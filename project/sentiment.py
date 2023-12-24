import requests
from bs4 import BeautifulSoup
import re
import nltk
from nltk.sentiment.vader import SentimentIntensityAnalyzer
nltk.download("stopwords")
nltk.download('punkt')
nltk.download('vader_lexicon')
import matplotlib.pyplot as plt


# Obtener el texto de la URL
url = "https://en.wikipedia.org/wiki/Document_classification"
response = requests.get(url)
text = response.text

# Parsear el texto con Beautiful Soup
soup = BeautifulSoup(text, "html.parser")
# Extraer el texto de los elementos 'p'
article_text = [p.text for p in soup.find_all("p")]
#with open('output.txt', 'w') as f:
#    for paragraph in article_text:
 #       f.write(paragraph + '\n')
num_words = sum(len(p.split()) for p in article_text)
print("Number of words: " + str(num_words))
# Combina todos los párrafos en una única cadena de texto
full_text = ' '.join(article_text)
# Ahora divide full_text en segmentos de 1000 caracteres
segments = [full_text[i:i + 1000] for i in range(0, len(full_text), 1000)]
num_segments = len(segments)
print("cantidad de segments " + str(num_segments))
# imports the stopwords corpus from NLTK
from nltk.corpus import stopwords
stop_words = set(stopwords.words('english'))

# Preprocesar el texto

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
print("cantidad de sentiments " + str(num_segments))
 # Obtener la puntuación del  "compound score"
compound_scores = [sentiment['compound'] for sentiment in sentiments]
# crear histograma
print (compound_scores)
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
    plt.savefig(f'segment_{i}.png')  # Save the image as 'segment_0.png', 'segment_1.png', etc.
    plt.clf()  # Clear the figure for the next plot


average_sentiment = sum(compound_scores) / len(compound_scores)


# Imprimir la puntuación del sentimiento promedio
print(average_sentiment)
