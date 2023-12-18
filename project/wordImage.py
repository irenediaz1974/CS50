from wordcloud import WordCloud
import matplotlib.pyplot as plt
import numpy as np
from PIL import Image
from nltk.corpus import stopwords


# wordcloud function
def word_cloud():
    with open('static\orgullo.txt', 'r') as f:
        text = f.read()
        spanish_stopwords = set(stopwords.words('spanish'))
        #frame_mask=np.array(Image.open("cloud_shape.png"))
        wordcloud = WordCloud(stopwords=spanish_stopwords, background_color="white", width=800, height=400).generate(text)
        #plt.imshow (wordcloud, interpolation='bilinear')
        #plt.axis("off")
        plt.imshow (wordcloud)
        plt.show()

word_cloud()


