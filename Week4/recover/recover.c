#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

    int file_c = 0;
    char filename[20];
    typedef uint8_t BYTE;
    BYTE buffer[512];

    // ensure proper usage
    if (argc != 2)
    {
        printf("need infile\n");
        return 1;
    }

    // filename to recover
    char *infile = argv[1];

    // open file to recover
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    FILE *pfile;

    int OpenF = 0;

    while (true)
    {

        size_t bytesRead = fread(buffer, sizeof(BYTE), 512, inptr);

        if (bytesRead < 512)
        {
            if (feof(inptr))
            {
                // End of file reached, handle accordingly
                fclose(inptr);
                break;
            }
            else
            {
                // An error occurred, handle accordingly
                fclose(inptr);
                break;
            }
        }

        // Continue with your code here

        for (int i = 0; i <= 512 - 4; i++)
        {
            if ((buffer[i] == 0xff) && (buffer[i + 1] == 0xd8) && (buffer[i + 2] == 0xff) && ((buffer[i + 3] & 0xf0) == 0xe0))
            {

                // found a header , ask if there is a file open
                if (OpenF == 1)
                {
                    fclose(pfile);
                    sprintf(filename, "%03i.jpg", file_c);
                    file_c += 1;
                    pfile = fopen(filename, "w");
                }
                else
                {
                    sprintf(filename, "%03i.jpg", file_c);
                    pfile = fopen(filename, "w");
                    OpenF = 1;
                    file_c += 1;
                }
            }
        }

        if (OpenF == 1)
        {

            fwrite(buffer, sizeof(BYTE), 512, pfile);
        }
    }

    // close infile
    fclose(pfile);
    return 0;
}