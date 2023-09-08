// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];


void sort_cities(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
//  applying bubble sort.
// Pseudocode: 
                // set swap counter to a non-zero value
                    // repeat until the  swap counter is 0
                         // look at each adjacent pair
                         //   If two adjacent elements are not in order,
                                // swap them and add 1 to swap_counter


void sort_cities(void)
{

    int swap_counter=-1 ;
    string name_city1 = "";
    int temp_city1 ;

    while (swap_counter != 0)
    {
        swap_counter=0;    
        for (int i = NUM_CITIES - 1; i >  0 ; i--)
        {
            if ( temps[i].temp > temps[i - 1].temp)
            {
                swap_counter+=1;
                temp_city1 = temps[i].temp ;
                name_city1 = temps[i].city;
                // Swap
                temps[i].temp= temps[i-1].temp;
                temps[i].city= temps[i-1].city;
                temps[i-1].city= name_city1;
                temps[i-1].temp= temp_city1;
            }
        
        }
      
    }   
}
