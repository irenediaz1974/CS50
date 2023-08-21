// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])

{
    int replace(string cadena);

    //todo: evaluar entrada de la llamada al programa, devolver 1 si no hay argumentos o son mas de 2
    if (argc = 1)
        {
         // llamar a la funcion replace que cambia las vocales de la cadena que se paso como argumento

        string cadena= argv[1];

        replace(cadena);

        }
    else
        {
            printf("el valor de la cadena %i", argc);
            return 1;
        }
}

int replace(string cadena)
{

int n=strlen(cadena);

    for (int i= 0; i < n; i++)
            {
                 char letra = cadena[i];
                 switch (letra)
                    {
                         case 'a':
                            printf("6");
                            break;
                        case 'e':
                            printf("3");
                            break;
                        case 'i':
                            printf("1");
                            break;
                        case 'o':
                            printf("0");
                            break;
                        default:
                            printf("%c", letra);
                            break;
                    }
          }
return 1;
}