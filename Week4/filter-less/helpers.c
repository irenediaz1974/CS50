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

      
    }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE fullrow[height][width];

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            // Read pixel and save it in a tmp rbgtriple
             fullrow[x][y] = image[x][y];

        }
    }
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int blue=0x0 , green=0x0 , red=0x0 ;
             // left up corner
            if ((i == 0) && (j == 0))
            {
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                         blue = blue + fullrow[x][y].rgbtBlue;
                         green = green + fullrow[x][y].rgbtGreen;
                         red = red + fullrow[x][y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue= (float) roundf ( blue / 4.0) ;
                image[i][j].rgbtGreen= (float) roundf ( green / 4.0)  ;
                image[i][j].rgbtRed= (float) roundf ( red / 4.0) ;
                blue =  0x0;
                green= 0x0;
                red= 0x0;                    
              }
            // right up corner
            if ((i == 0) && (j == width - 1))
            {
                for (int x = 0; x <= 1; x++)
                {
                    for (int y = width - 2 ; y <=  width - 1; y++)
                    {
                         blue = blue + fullrow[x][y].rgbtBlue;
                         green = green + fullrow[x][y].rgbtGreen;
                         red = red + fullrow[x][y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue= (float) roundf ( blue / 4.0) ;
                image[i][j].rgbtGreen= (float) roundf ( green / 4.0)  ;
                image[i][j].rgbtRed= (float) roundf ( red / 4.0) ;
                blue =  0x0;
                green= 0x0;
                red= 0x0;                    
            }
             // left down corner
            if ((i == height - 1) && (j == 0))
            {
                for (int x = height - 2 ; x <= height - 1; x++)
                {
                    for (int y = 0; y <= 1; y++)
                    {
                        blue = blue + fullrow[x][y].rgbtBlue;
                        green = green + fullrow[x][y].rgbtGreen;
                        red = red + fullrow[x][y].rgbtRed;
                    }
                }
                image[i][j].rgbtBlue= (float) roundf ( blue / 4.0) ;
                image[i][j].rgbtGreen= (float) roundf ( green / 4.0)  ;
                image[i][j].rgbtRed= (float) roundf ( red / 4.0) ;
                blue =  0x0;
                green= 0x0;
                red= 0x0;                 
            }
               // right down corner
            if ((i == height - 1) && (j == width - 1))
            {
                  for (int x = height - 2 ; x <= height - 1; x++)
                    {
                        for (int y = width - 2 ; y <=  width - 1; y++)
                        {
                         blue = blue + fullrow[x][y].rgbtBlue;
                         green = green + fullrow[x][y].rgbtGreen;
                         red = red + fullrow[x][y].rgbtRed;
                        }
                    }
                image[i][j].rgbtBlue= (float) roundf ( blue / 4.0) ;
                image[i][j].rgbtGreen= (float) roundf ( green / 4.0)  ;
                image[i][j].rgbtRed= (float) roundf ( red / 4.0) ;
                blue =  0x0;
                green= 0x0;
                red= 0x0;                 
            }              
              //middle pixel
              if ( (i >= 1 && i <= height -2) && (j >= 1 && j <= width - 2))
              {
                  for (int x= i - 1; x <= i + 1; x++)
                    {
                       for (int y = j - 1; y <= j + 1; y++)
                        {
                            blue = blue + fullrow[x][y].rgbtBlue;
                            green = green + fullrow[x][y].rgbtGreen;
                            red = red + fullrow[x][y].rgbtRed;
                        }
                    }
                image[i][j].rgbtBlue= (float) roundf ( blue / 9.0) ;
                image[i][j].rgbtGreen= (float) roundf ( green / 9.0)  ;
                image[i][j].rgbtRed= (float) roundf ( red / 9.0) ;
                blue =  0x0;
                green= 0x0;
                red= 0x0;
              } 
        }
    }

 return;
}

