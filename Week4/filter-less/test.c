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


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
             int blue=0x0, green=0x0,  red=0x0;

             if (i==0 && j== 0)
             {

                  else if (j == width -1)
                  {
                    // sumar D,G,H,E (G = fullrow[i + 1][j-1] , H = fullrow[i+ 1][j])
                    image[i][j].rgbtBlue= (int) round ((fullrow[i][j].rgbtBlue + fullrow[i][j - 1].rgbtBlue
                       + fullrow[i + 1][j - 1].rgbtBlue + fullrow[i + 1][j].rgbtBlue) / 4) ;
                    image[i][j].rgbtGreen= (int) round ((fullrow[i][j].rgbtGreen + fullrow[i][j - 1].rgbtGreen
                       + fullrow[i + 1][j - 1].rgbtGreen+ fullrow[i + 1][j].rgbtGreen) / 4) ;
                     image[i][j].rgbtRed= (int) round ((fullrow[i][j].rgbtRed + fullrow[i][j - 1].rgbtRed
                       + fullrow[i + 1][j - 1].rgbtRed+ fullrow[i + 1][j].rgbtRed) / 4) ;
                  }
	                else if  (j > 0 && j < width -1)
                  {
                      for (int x = 0; x <=  1; x++)
                      {
                        for (int y = j - 1; y <= j + 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 6;
                    image[i][j].rgbtGreen= green / 6;
                    image[i][j].rgbtRed= red / 6;
                    blue=0;
                    green=0;
                    red=0;
                  }
             }

            else if  ( i== height -1)
            {
                  if (j == 0 && (i== height -1))
                  {
                    for (int x = height - 2; x <=  height - 1 ; x++)
                      {
                        for (int y = 0; y <= 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 4;
                    image[i][j].rgbtGreen= green / 4;
                    image[i][j].rgbtRed= red / 4;
                    blue=0;
                    green=0;
                    red=0;
                  }
                  else if (j== width -1 && (i== height -1))
                  {

                    for (int x = height - 2; x <=  height - 1 ; x++)
                      {
                        for (int y = 0; y <= 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 4;
                    image[i][j].rgbtGreen= green / 4;
                    image[i][j].rgbtRed= red / 4;
                    blue=0;
                    green=0;
                    red=0;

                  }
                  else if (j > 0 && j < width -1 && (i== height -1))
                   {
                    // sumar A,B,D,E, C, F -- C=fullrow[i-1][j+1] F= fullrow[i][j+1]

                       for (int x = height - 2; x <=  height - 1 ; x++)
                      {
                        for (int y = j - 1; y <= j + 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 6;
                    image[i][j].rgbtGreen= green / 6;
                    image[i][j].rgbtRed= red / 6;
                    blue=0;
                    green=0;
                    red=0;
                   }
            }

            else if ( i > 0 &&  i < height -1)
            {
                    if  (j== 0 && ( i > 0 &&  i < height -1))
                    {
                            //sumar B,C,E,F,H,I

                      for (int x = i - 1; x <=  i + 1 ; x++)
                      {
                        for (int y = 0 ; y <= j + 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 6;
                    image[i][j].rgbtGreen= green / 6;
                    image[i][j].rgbtRed= red / 6;
                    blue=0;
                    green=0;
                    red=0;
                    }

                  else if (j == width - 1 && ( i > 0 &&  i < height -1))
                  {
                     for (int x = i - 1; x <=  i + 1 ; x++)
                      {
                        for (int y = width - 2  ; y <= width - 1; y++)
                        {
                          blue += fullrow[x][y].rgbtBlue;
                          green += fullrow[x][y].rgbtGreen;
                          red +=  fullrow[x][y].rgbtRed;
                        }
                      }
                    image[i][j].rgbtBlue= blue / 6;
                    image[i][j].rgbtGreen= green / 6;
                    image[i][j].rgbtRed= red / 6;
                    blue=0;
                    green=0;
                    red=0;


                  }

                  else if   ( ( i > 0  &&  i < height -1) && (j > 0 && j < width - 1))
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
                    image[i][j].rgbtBlue= blue / 9.0;
                    image[i][j].rgbtGreen= green / 9.0;
                    image[i][j].rgbtRed= red / 9.0;
                    blue=0;
                    green=0;
                    red=0;
                  }
            }
        }
    }
 return;
}