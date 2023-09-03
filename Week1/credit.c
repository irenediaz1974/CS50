#include <cs50.h>
#include <math.h>
#include <ctype.h>
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
     // string type_target = type_tarjet(number);
     printf("/n es valida!!!");
    }
    else
    {
        printf("/n no valida");
    }

}

long get_number(void)
{
    // TODO
    long n;
    long size_max=0;
    long size_min=0;

    //do
    {
        n = get_long_long("Number: ");
        
        //size_max= n / 1e16;
       // size_min= n / 1e12 ;
    }
    //while ( size_min < 1 || size_max > 1);

    return n;
}

bool cheksum_target(long number)
{
    int n_tar=1;
    int sum_right=0;
    int sum_left=0;
    long targ=number;
    // sum digit left to right start with last digit
    while (n_tar>=1) 
        {
            n_tar=number % 10;
            sum_left=sum_left+ n_tar;
            printf("number is: %i", n_tar);
            number= number * 0.01;
        }
    n_tar=1;
    number=targ * 0.1;
    //sum digit left to right start with last second digit
    while (n_tar>=1)  
        {
            n_tar=number % 10;
            //sum digit if multip by two is greater than 10
            if ((2 *(n_tar)) > 9)
                {
                    int n_digit=n_tar;
                    n_digit= 2 *(n_tar);

                    sum_right= sum_right + n_digit % 10;
                    n_digit= n_digit * 0.1;

                    sum_right= sum_right + n_digit % 10;
                }
            else
                {
                    sum_right=sum_right+ 2 *(n_tar);
                }

            printf("number is: %i", n_tar);
            number= number * 0.01;
        }
    int sum_total= sum_right + sum_left;
    if ((sum_total % 10)>0)
    {
        return false;
    }
    else
    {
        return true;
    }
  
}






string type_tarjet(long number)
{
    printf("tipo\n");
    string type_tar= "VISA";
    return type_tar;
}