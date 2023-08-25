#include <cs50.h>
#include <math.h>
#include <stdio.h>


int main(void)
{
   long n=get_long("Tarjeta: ");
   printf("el valor de n es %li, el valor de la potencia es: %li, el valor del modulo es: %li", n, n*pow(10,13), n % pow(10,13));
   return 1;
}