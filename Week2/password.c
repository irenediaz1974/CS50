// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{

    // recorrer cadena y contar ( 1 num, 1 uppercase, 1 lowercase, 1 special character)

    int n = strlen(password);

    int counter[4];

    for (int i = 0; i < n; i++)
    {
        char c = password[i];

        if (isdigit(c))
        {
            counter[0] = 1;
        }

        if (islower(c))
        {
            counter[1] = 1;
        }

        if (isupper(c))
        {
            counter[2] = 1;
        }
        if (isalnum(c) == 0)
        {
            counter[3] = 1;
        }
    }
    if ((counter[0] + counter[1] + counter[2] + counter[3]) == 4)
    {
        return true;
    }
    else
    {
        return false;
    }
}