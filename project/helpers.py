import requests
from bs4 import BeautifulSoup
import nltk
from nltk.sentiment import SentimentIntensityAnalyzer

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score
import pandas as pd

import re

# define the function to scrape the website
def scrape_website(url):
    response = requests.get(url)
    if response.status_code == 200:
        soup = BeautifulSoup(response.text, "html.parser")
        # define the tags to be extracted from the website
        tags = soup.find_all("h2")
        # write the extracted data to a file
        with open("data.txt", "w") as f:
            for tag in tags:
                 f.write(tag.text + "\n")
        print("Data has been scraped and stored in data.txt.")
    else:
        print("Unable to connect to the website. Please try again later.")


# Analizing text sentiment using Natural language processing techniques
def analyze_sentiment(text):
    sia = SentimentIntensityAnalyzer()
    sentiment = sia.polarity_scores(text)
    if sentiment['compound'] >= 0.05:
        return 'Positive'
    elif sentiment['compound'] <= -0.05:
        return 'Negative'
    else:
        return 'Neutral'
    
# Readability from Week6
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
        print("Before Grade 1")
    elif index > 1 and index < 16:
        print("Grade " + str(index))
    else:
        print("Grade 16+")


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





# Evaluate the text's accuracy using pandas
data = pd.read_csv('text_data.csv')
# Convert to lowercase
data['text'] = data['text'].apply(lambda x: " ".join(x.lower() for x in x.split())) 
data['text'] = data['text'].str.replace('[^\w\s]', '')
 # Remove punctuation
stop_words = set(nltk.corpus.stopwords.words('english'))
# Remove stop words
data['text'] = data['text'].apply(lambda x: " ".join(x for x in x.split() if x not in stop_words)) 
# Split data into training and testing sets
train_data = data.sample(frac=0.8, random_state=1)
test_data = data.drop(train_data.index)
# Vectorize text data
vectorizer = CountVectorizer()
X_train = vectorizer.fit_transform(train_data['text'])
X_test = vectorizer.transform(test_data['text'])
# Train and fit the classifier
classifier = MultinomialNB()
y_train = train_data['category']
classifier.fit(X_train, y_train)
# Make predictions on test data
y_pred = classifier.predict(X_test)
# Evaluate accuracy
accuracy = accuracy_score(test_data['category'], y_pred)
print("Accuracy: {:.2f}%".format(accuracy * 100))