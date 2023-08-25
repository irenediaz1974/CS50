#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int count_letters(string text);

    int count_words(string text);

    int count_sentences(string text);

    string texto = get_string("Text:");

    double c_let = count_letters(texto);
    double c_words = count_words(texto);
    double c_sent = count_sentences(texto);

    double L = (c_let / c_words) * 100;
    double S = (c_sent / c_words) * 100;

    int index = (int) round((0.0588 * L) - (0.296 * S) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 1 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int count_sentences(string text)
{
    int n = strlen(text);

    int c_sentences = 0;

    for (int i = 0; i < n; i++)
    {
        char c = text[i];

        if (c == '!' || c == '?' || c == '.')
        {
            c_sentences = c_sentences + 1;
        }
    }
    return c_sentences;
}

int count_words(string text)
{
    int n = strlen(text);

    int c_spaces = 1;

    for (int i = 0; i < n; i++)
    {
        char c = text[i];
        if (isspace(c))
        {
            c_spaces = c_spaces + 1;
        }
    }
    return c_spaces;
}

int count_letters(string text)
{
    int n = strlen(text);
    int c_letters = 0;

    for (int i = 0; i < n; i++)
    {
        char c = text[i];

        if (isalpha(c))
        {
            c_letters = c_letters + 1;
        }
    }
    return c_letters;
}