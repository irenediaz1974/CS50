#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;
int bits[8];

void print_bulb(int bit);
string get_sentence(void);
void to_binary(string s_message);
void convert_binary(int to_bit);

int main(void)
{
    string s_message = " ";
    // TODO
    // get string to convert
    s_message = get_sentence();
    // convert to binary and print
    to_binary(s_message);
    
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji to execute in code CS50 environment
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji to execute in code CS50 environment
        printf("\U0001F7E1");
    }
}

string get_sentence(void)
{
    string s_sent;

    s_sent = get_string("Message: ");

    return s_sent;
}

void to_binary(string s_message)
{
    int N = strlen(s_message);

    int to_bit = 0;

    for (int i = 0; i < N; i++)
    {
        to_bit = (s_message[i]);
        // call convert_binary to convert a ascii value to binary
        convert_binary(to_bit);
        // call print_bulb to print word
        for (int j = 0; j < BITS_IN_BYTE; j++)
        {
            print_bulb(bits[j]);
        }
        printf("\n");
    }
}

void convert_binary(int to_bit)
{
    int n_data = to_bit;

    for (int i = 1; i < BITS_IN_BYTE; i++)
    {
        // to know is right most bit is 0 or 1 (even)

        if (n_data % 2 == 0)
        {
            bits[BITS_IN_BYTE - i] = 0;
        }
        else
        {
            bits[BITS_IN_BYTE - i] = 1;
        }

        n_data = n_data / 2;
    }
}
