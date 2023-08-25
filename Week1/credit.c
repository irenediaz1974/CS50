#include <cs50.h>
#include <math.h>
#include <stdio.h>


long get_number(void);
bool cheksum_target(long target);
string type_tarjet(long number);


int main(void)
{
    // Ask target number
    long number = get_number();


    // Calculate the checksum
    bool target_real= cheksum_target(number);


    // Type of target, visa, mastercard...
    if (target_real)
    {
     string type_target = type_tarjet(number);
    }
    else
    {
        printf("no valida");
    }

}

long get_number(void)
{
    // TODO
    long n;
    do
    {
      n = get_long("Change number: ");
    }
    while (n < pow(10,13) && n > pow(10,16));

    return n;
}

bool cheksum_target(long target)
{
    printf("cheksum\n");
    return true;
}

string type_tarjet(long number)
{
    printf("tipo\n");
    string type_tar= "VISA";
    return type_tar;
}      
    

