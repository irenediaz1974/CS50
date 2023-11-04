import re
from cs50 import get_string


def main():
    # prompt for text
    texto = get_string("Text:")
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


main()
