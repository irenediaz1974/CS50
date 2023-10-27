#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int hash (char *word );

int main (string argv[])
{
   int word= atoi(argv[1]);
   int value= hash(word);
    
return 0;
    
}

int hash (int word )
{
    int tmp=0;

    int n= strlen(word);
    
        if (n > 3)
        {
            for (int y=0; y < 3; y++)
            
            {
                 tmp= tmp + ((int) tolower(word[y]) - 'a');
            }
            
        }
    printf( "%s", tmp);
    return tmp;
}