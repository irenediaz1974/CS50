from wordcloud import WordCloud
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
from nltk.corpus import stopwords


# wordcloud function
def word_cloud():
    with open('static\libros\emma.txt', 'r') as f:
        text = f.read()
        stopwords_spanish = stopwords.words('english')
        newStopWords = ['could','must','would']
        stopwords_spanish.extend(newStopWords)
        #wordcloud = WordCloud(stopwords=spanish_stopwords, max_words = 40, background_color="white", colormap = "magma", width=800, height=400).generate(text)
        wordcloud = WordCloud(stopwords=stopwords_spanish, max_words = 400, background_color="lightgray",  colormap = "inferno", width=1200, height=750).generate(text)
        plt.axis("off")
        plt.imshow (wordcloud,interpolation = "bilinear")
        plt.show()

word_cloud()


