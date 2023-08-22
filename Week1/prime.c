#include <cs50.h>
#include <stdio.h>

bool prime(int number);

int main(void)
{
    int min;
    do
    {
        min = get_int("Minimum: ");
    }
    while (min < 1);

    int max;
    do
    {
        max = get_int("Maximum: ");
    }
    while (min >= max);

    for (int i = min; i <= max; i++)
    {
        if (prime(i))
        {
            printf("%i\n", i);
        }
    }
}

bool prime(int number)
{
    // realizar el ciclo hacia atras dividiendo por n-1 con un contador que cuente cuantas veces el modulo da 0, si counter>2 es primo, sino no

    int counter=1;

    int i=1;

    while ( i < number)
        {

            if ( number % (number - i) == 0)
                {
                    counter=counter + 1;
                }
        i = i + 1;
        }

    if (counter <= 2)
    {

        return true;
    }


    return false;
}


