#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Read pixel color values by rows and columns, and change the value by the average

            int tmp= (int) round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0) ;

            image[i][j].rgbtBlue = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtRed = tmp;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Read pixel color values by rows and columns, and change the value by the sepia formula

            int sepiaRed = (int) round(.393 * (image[i][j].rgbtRed) + .769 * (image[i][j].rgbtGreen) + .189 * (image[i][j].rgbtBlue)) ;
            int sepiaGreen = (int) round(.349 * (image[i][j].rgbtRed)  + .686 * (image[i][j].rgbtGreen) + .168 * (image[i][j].rgbtBlue));
            int sepiaBlue = (int) round(.272 * (image[i][j].rgbtRed)  + .534 * (image[i][j].rgbtGreen) + .131 * (image[i][j].rgbtBlue));

            if ( sepiaRed > 0xff )
            {
                sepiaRed= 0xff;
            }
             if ( sepiaGreen > 0xff )
            {
                sepiaGreen= 0xff;
            }
             if ( sepiaBlue > 0xff )
            {
                sepiaBlue= 0xff;
            }

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;


        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        RGBTRIPLE fullrow[height][width];

        for (int j = 0; j < width; j++)
        {
            // Read pixel and saveb it in a tmp rbgtriple
            fullrow[i][j].rgbtBlue = image[i][j].rgbtBlue;
            fullrow[i][j].rgbtGreen = image[i][j].rgbtGreen;
            fullrow[i][j].rgbtRed = image[i][j].rgbtRed;
        }

        for (int j = 0; j < width; j++)
        {
        //Read pixel and swap
          image[i][j].rgbtBlue = fullrow[i][(width -1) - j].rgbtBlue;
          image[i][j].rgbtGreen = fullrow[i][(width -1)- j].rgbtGreen ;
          image[i][j].rgbtRed = fullrow[i][(width -1) - j].rgbtRed;
        }
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE fullrow[height][width];
    RGBTRIPLE block3[3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            fullrow[i][j].rgbtBlue= image[i][j].rgbtBlue;
            fullrow[i][j].rgbtGreen= image[i][j].rgbtGreen;
            fullrow[i][j].rgbtRed= image[i][j].rgbtRed;
        }
    }


    return;
}
