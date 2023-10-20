#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int atoi(string s);
bool only_digits(string s);
char rotate(char c, int n);

int main(int argc, string argv[])
{

    if (argc == 2)
    {
        if (only_digits(argv[1]) == true)
        {
            int k = atoi(argv[1]);
            string text_to_cipher = get_string("plaintext:  ");
            int N = strlen(text_to_cipher);
            printf("ciphertext: ");
            for (int i = 0; i < N; i++)
            {
                text_to_cipher[i] = rotate(text_to_cipher[i], k);
                printf("%c", text_to_cipher[i]);
            }
            printf("\n");
        }
        else
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}

char rotate(char c, int n)
{
    char C;

    if (c >= 97 && c <= 122)
    {
        c = c - 97;
        if (c + n >= 26)
        {
            C = (c + n) % 26;
        }
        else
        {
            C = c + n;
        }

        C = C + 97;
    }
    else if (c >= 65 && c <= 90)
    {
        c = c - 65;
        if (c + n >= 26)
        {
            C = (c + n) % 26;
        }
        else
        {
            C = c + n;
        }
        C = C + 65;
    }
    else
    {
        C = c;
    }
    return C;
}

bool only_digits(string s)
{
    int N = strlen(s);
    for (int i = 0; i < N; i++)
    {
        if (isdigit(s[i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return false;
        }
    }
    return true;
}