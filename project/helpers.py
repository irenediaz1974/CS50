import os
import re
from cs50 import get_string
import requests
from bs4 import BeautifulSoup
import nltk
from nltk.sentiment.vader import SentimentIntensityAnalyzer
from nltk import word_tokenize, pos_tag, ne_chunk
nltk.download("stopwords")
nltk.download('punkt')
nltk.download('vader_lexicon')
nltk.download('averaged_perceptron_tagger')
nltk.download('maxent_ne_chunker')
nltk.download('words')
# imports the stopwords corpus from NLTK
from nltk.corpus import stopwords
stop_words = set(stopwords.words('english'))
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt

from flask import  render_template

def obtener_estadisticas(url): 
    # Obtener el texto de la URL
    #url = "https://en.wikipedia.org/wiki/Document_classification"
    response = requests.get(url)
    text = response.text
    # Parsear el texto con Beautiful Soup
    soup = BeautifulSoup(text, "html.parser")
    # Extraer el texto de los elementos 'p'
    article_text = [p.text for p in soup.find_all("p")]
 
    num_words = sum(len(p.split()) for p in article_text)
    # Combina todos los párrafos en una única cadena de texto
    full_text = ' '.join(article_text)
    # Ahora divide full_text en segmentos de 1000 caracteres
    segments = [full_text[i:i + 1000] for i in range(0, len(full_text), 1000)]
    num_segments = len(segments)
    print("cantidad de segments " + str(num_segments))
    # Preprocesar el text
    processed_segments = []
    for segment in segments:
        # Tokenize the segment
        tokens = nltk.word_tokenize(segment)
        # Remove stopwords, digits, and punctuation
        processed_tokens = [token for token in tokens if token not in stop_words and not token.isdigit() and token.isalpha()]
        # Join the processed tokens back into a segment
        processed_segment = ' '.join(processed_tokens)
        # Append the processed segment to the processed_segments list
        processed_segments.append(processed_segment)
    # Analizar el sentimiento de cada segmento
    sentiments = []
    for segment in processed_segments:
        tokens = nltk.word_tokenize(segment)
        # Obtener la puntuación del sentimiento
        sentiment = nltk.sentiment.vader.SentimentIntensityAnalyzer().polarity_scores(" ".join(tokens))
        # Agregar la puntuación del sentimiento a la lista
        sentiments.append(sentiment)
    num_segments = len(sentiments)
    # Obtener la puntuación del  "compound score"
    compound_scores = [sentiment['compound'] for sentiment in sentiments]
    # print (compound_scores)
    average_sentiment = sum(compound_scores) / len(compound_scores)
    # crear histograma
    plt.hist(compound_scores, bins=10)
    plt.xlabel('Compound Score')
    plt.ylabel('Frequency')
    plt.title('Distribution of Sentiment Scores')
    plt.savefig('static/img/histogram.png')
    plt.clf()
    # crear pastel por cada segmento de 1000 caracteres
    for i, sentiment in enumerate(sentiments):
        values = [sentiment['neg'], sentiment['neu'], sentiment['pos']]
        labels = ['Negativo', 'Neutral', 'Positivo']
        plt.pie(values, labels=labels)
        plt.legend(['Negativo', 'Neutral', 'Positivo'])
        plt.savefig(f'static/img/segment_{i}.png')  # Save the image as 'segment_0.png', 'segment_1.png', etc.
        plt.clf()  # Clear the figure for the next plot
    # Imprimir la puntuación del sentimiento promedio
    print("promedio de sentiment" + str(average_sentiment))
    return (num_words, num_segments, average_sentiment, compound_scores)


def readability(texto):
    # Call function Count letters
    c_let = count_letters(texto)
    # Call function Count words
    c_words = count_words(texto)
    # Call function Count sentences
    c_sent = count_sentences(texto)
    #  Índice de Legibilidad de Coleman-Liau
    L = (c_let / c_words) * 100
    S = (c_sent / c_words) * 100
    index = round((0.0588 * L) - (0.296 * S) - 15.8)
    if index < 1:
        return (" Grado 1 Fácil de Leer")
    elif index > 1 and index < 12:
        return("Grado " + str(index) + ".  Fácil de entender" )
    elif index >= 12 and index < 16:
        return("Grado " + str(index) + "> 12. Legibilidad moderada" )
    else:
        return("Grado 16+ (Dificil de leer)")


def count_letters(text):
    matches = re.findall("[a-zA-Z]", text)
    count = len(matches)
    return count


def count_words(text):
    matches = text.split()
    count = len(matches)
    return count


def count_sentences(text):
    matches = re.findall("[.!?]", text)
    count = len(matches)
    return count


def apology(message, code=400):
    """Render message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code



def resumen(sentence):

    tokens = word_tokenize(sentence)
    pos_tags = pos_tag(tokens)
    named_entities = ne_chunk(pos_tags)
    entidades = []
    for nodo in named_entities:
        if isinstance(nodo, nltk.Tree):
            entidades.append({"tipo": nodo.label(), "tokens": [token for token, pos in nodo.leaves()]})
    return entidades
