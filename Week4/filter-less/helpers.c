#include "helpers.h"
#include <math.h>

void fill_zero(int x, int y, RGBTRIPLE matrix[3][3]);

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

// Blur image. Find the average of the near pixels
void blur(int height, int width, RGBTRIPLE image[height][width])
{
 
 RGBTRIPLE(*matrix)[3] = calloc(3, 3* sizeof(RGBTRIPLE));

  for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix[i][j].rgbtBlue =0x0;
            matrix[i][j].rgbtGreen = 0x0;
            matrix[i][j].rgbtRed = 0x0;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {        
            // First row of matrix
            if (image[i-1][j-1].rgbtBlue!=NULL)
            {
                matrix[0][0].rgbtBlue= image[i-1][j-1].rgbtBlue;
                matrix[0][0].rgbtGreen=image[i-1][j-1].rgbtGreen;
                matrix[0][0].rgbtRed = image[i-1][j-1].rgbtRed;
            } 
           
           if (image[i-1][j].rgbtBlue!=NULL)
            {
                matrix[0][1].rgbtBlue= image[i-1][j].rgbtBlue;
                matrix[0][1].rgbtGreen=image[i-1][j].rgbtGreen;
                matrix[0][1].rgbtRed = image[i-1][j].rgbtRed;
            } 
            if (image[i-1][j+1].rgbtBlue!=NULL)
            {
                matrix[0][2].rgbtBlue= image[i-1][j+1].rgbtBlue;
                matrix[0][2].rgbtGreen=image[i-1][j+1].rgbtGreen;
                matrix[0][2].rgbtRed = image[i-1][j+1].rgbtRed;
            } 
            //second row of matrix
            if (image[i][j-1].rgbtBlue!=NULL)
            {
                matrix[1][0].rgbtBlue= image[i][j-1].rgbtBlue;
                matrix[1][0].rgbtGreen=image[i][j-1].rgbtGreen;
                matrix[1][0].rgbtRed = image[i][j-1].rgbtRed;
            } 
            if (image[i][j].rgbtBlue!=NULL)
            {
                matrix[1][1].rgbtBlue= image[i][j].rgbtBlue;
                matrix[1][1].rgbtGreen=image[i][j].rgbtGreen;
                matrix[1][1].rgbtRed = image[i][j].rgbtRed;
            } 
            if (image[i][j+1].rgbtBlue!=NULL)
            {
                matrix[1][2].rgbtBlue= image[i][j+1].rgbtBlue;
                matrix[1][2].rgbtGreen=image[i][j+1].rgbtGreen;
                matrix[1][2].rgbtRed = image[i][j+1].rgbtRed;
            } 
            //third row
             if (image[i+1][j-1].rgbtBlue!=NULL)
            {
                matrix[2][0].rgbtBlue= image[i+1][j-1].rgbtBlue;
                matrix[2][0].rgbtGreen=image[i+1][j-1].rgbtGreen;
                matrix[2][0].rgbtRed = image[i+1][j-1].rgbtRed;
            } 
            if (image[i+1][j].rgbtBlue!=NULL)
            {
                matrix[2][1].rgbtBlue= image[i+1][j].rgbtBlue;
                matrix[2][1].rgbtGreen=image[i+1][j].rgbtGreen;
                matrix[2][1].rgbtRed = image[i+1][j].rgbtRed;
            } 
            if (image[i+1][j+1].rgbtBlue!=NULL)
            {
                matrix[2][2].rgbtBlue= image[i+1][j+1].rgbtBlue;
                matrix[2][2].rgbtGreen=image[i+1][j+1].rgbtGreen;
                matrix[2][2].rgbtRed = image[i+1][j+1].rgbtRed;
            } 

            int Blue=0x0;
            int Green=0x0;
            int Red=0x0;
            int counter_ave=0;
            for (int i = 0; i < 3; i++)
            {
                 for (int j = 0; j < 3; j++)
                {
                    if (matrix[i][j].rgbtBlue!= 0 || matrix[i][j].rgbtGreen!= 0 || matrix[i][j].rgbtRed!= 0 )
                    {
                        counter_ave+=1;
                        Blue=  matrix[i][j].rgbtBlue;
                        Green= matrix[i][j].rgbtGreen;
                        Red= matrix[i][j].rgbtRed;
                    }               
                }
            }
        // update the pixels in the image
        image[i][j].rgbtBlue = Blue/ counter_ave;
        image[i][j].rgbtGreen = Green / counter_ave ;
        image[i][j].rgbtRed = Red / counter_ave;
        }
   }
}
