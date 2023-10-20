// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])

{
    string replace(string cadena);

    //todo: evaluar entrada de la llamada al programa, devolver 1 si no hay argumentos o son mas de 2

    if (argc == 2)
        {
         // llamar a la funcion replace que cambia las vocales de la cadena que se paso como argumento

        string cadena= argv[1];

        printf("%s\n", replace(cadena));
        }
    else
        {
            printf("Usage: %s word \n", argv[0]);
            return 1;
        }
}

string replace(string cadena)
    {

    int n=strlen(cadena);

    for (int i= 0; i < n; i++)
            {
                 char letra = cadena[i];

                 switch (letra)
                    {
                         case 'a':
                            letra='6';
                            break;
                        case 'e':
                            letra='3';
                            break;
                        case 'i':
                            letra='1';
                            break;
                        case 'o':
                            letra='0';;
                            break;
                    }
               cadena[i]=letra;
          }
    return (cadena);
 }

