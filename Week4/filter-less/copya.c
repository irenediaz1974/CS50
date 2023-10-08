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
 
 RGBTRIPLE fullrow[height][width];

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            fullrow[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // si es primera- ultima fila o primera- ultima columna
           if ((i == 0 && (j >= 0 && j <= width - 1)) || ((i >= 0 && i <= height - 1) && j == 0)|| (i == height - 1 && (j >= 0 && j <= width - 1))|| ((i >= 0 && i <= height -1) && j == width - 1))
            {
                //si es esquina
                if ((i == 0 && j == 0)
                    || (i == 0 && j == width - 1)
                    || (i == height - 1 && j == 0)
                    || (i == height - 1 && j == width - 1))
                {
                    if (i == 0 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                    }

                    if (i == 0 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i +1 ][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j + 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j + 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j + 1].rgbtBlue) / 4.0);
                    }

                    if (i == height - 1 && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j - 1].rgbtRed) / 4.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j - 1].rgbtGreen) / 4.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j - 1].rgbtBlue) / 4.0);
                    }
                }
                // if not a corner index
                else
                {
                    if (i == 0 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height - 2) && j == 0)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i + 1][j + 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) / 6.0);
                    }

                    if (i == height - 1 && (j >= 1 && j <= width - 2))
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i - 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue) / 6.0);
                    }

                    if ((i >= 1 && i <= height -2) && j == width - 1)
                    {
                        image[i][j].rgbtRed = (int) round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i + 1][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 6.0);
                        image[i][j].rgbtGreen = (int) round((copy[i][j].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen) / 6.0);
                        image[i][j].rgbtBlue = (int) round((copy[i][j].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue) / 6.0);
                    }
                }
            }
            // for normal pixel no edge at all
            else
            {
                image[i][j].rgbtRed = (int) round(((copy[i - 1][j - 1].rgbtRed) + (copy[i - 1][j].rgbtRed) + (copy[i - 1][j + 1].rgbtRed) + (copy[i][j - 1].rgbtRed) + (copy[i][j].rgbtRed) + (copy[i][j + 1].rgbtRed) + (copy[i + 1][j - 1].rgbtRed) + (copy[i + 1][j].rgbtRed) + (copy[i + 1][j + 1].rgbtRed)) / 9.0);
                image[i][j].rgbtGreen = (int) round(((copy[i - 1][j - 1].rgbtGreen) + (copy[i - 1][j].rgbtGreen) + (copy[i - 1][j + 1].rgbtGreen) + (copy[i][j - 1].rgbtGreen) + (copy[i][j].rgbtGreen) + (copy[i][j + 1].rgbtGreen) + (copy[i + 1][j - 1].rgbtGreen) + (copy[i + 1][j].rgbtGreen) + (copy[i + 1][j + 1].rgbtGreen)) / 9.0);
                image[i][j].rgbtBlue = (int) round(((copy[i - 1][j - 1].rgbtBlue) + (copy[i - 1][j].rgbtBlue) + (copy[i - 1][j + 1].rgbtBlue) + (copy[i][j - 1].rgbtBlue) + (copy[i][j].rgbtBlue) + (copy[i][j + 1].rgbtBlue) + (copy[i + 1][j - 1].rgbtBlue) + (copy[i + 1][j].rgbtBlue) + (copy[i + 1][j + 1].rgbtBlue)) / 9.0);
            }

        }
    }

    return;
}