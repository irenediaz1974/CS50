#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int n_init;
    do
    {
        n_init = get_int("Say llamas initial number: ");
    }
    while (n_init < 9);

    // TODO: Prompt for end size

    int n_end;
    do
    {
        n_end = get_int("Say llamas end number: ");
    }
    while (n_end < n_init);

    // TODO: Calculate number of years until we reach threshold

    int n = 0;

    while (n_init < n_end)
    {
        n_init = n_init + ((n_init / 3) - (n_init / 4));

        n = n + 1;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}
