import requests
from bs4 import BeautifulSoup
import nltk

# Obtener el texto de la URL
url = "https://www.bbc.com/news/world-us-canada-60866817"
response = requests.get(url)
text = response.text

# Parsear el texto con Beautiful Soup
soup = BeautifulSoup(text, "html.parser")
article_text = soup.find_all("p")

# Dividir el texto en segmentos
segments = [article_text[i:i + 1000] for i in range(0, len(article_text), 1000)]

# Preprocesar el texto
for segment in segments:
    # Eliminar signos de puntuación
    stop_words = nltk.corpus.stopwords.words("english")
    processed_text = [word for word in segment if word not in stop_words and not word.isdigit()]

    # Tokenizar el texto
    tokens = nltk.word_tokenize(processed_text)

# Analizar el sentimiento de cada segmento
sentiments = []
for segment in segments:
    # Obtener la puntuación del sentimiento
    sentiment = nltk.sentiment.vader.SentimentIntensityAnalyzer().polarity_scores(" ".join(tokens))

    # Agregar la puntuación del sentimiento a la lista
    sentiments.append(sentiment)

# Obtener la puntuación del sentimiento promedio
average_sentiment = sum(sentiments.values()) / len(sentiments)

# Imprimir la puntuación del sentimiento promedio
print(average_sentiment)




