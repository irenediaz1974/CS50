#include <cs50.h>
#include <stdio.h>

int get_size(void);
void print_matrix(int n);

int main(void)
{
    // Get input only if is a number
    int n = get_size();
    // print
    print_matrix(n);
}

void print_matrix(int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}

int get_size(void)
{
    int n;
    do
    {
        n = get_int("Size: ");
    }
    while (n < 1 || n > 8);

    return n;
}
