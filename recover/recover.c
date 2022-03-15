#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCKSIZE 512
int main(int argc, char *argv[])
{
    // takes only one argument
    if (argc != 2)
    {
        printf("Usage : ./recover image\n");
        return 1;
    }
    if (argv[1] == NULL)
    {
        printf("Usage : ./recover image\n");
        return 1;
    }

    // initialize things for later use
    char filename[8];
    uint8_t buffer[BLOCKSIZE];
    int a = 0;
    FILE *output_pointer = NULL;

    //jpeg signature
    //bool header = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);

    // open memory card
    FILE *file = fopen(argv[1], "r");

    // if image can't be opened
    if (file == NULL)
    {
        printf("Unable to open file: %s\n", argv[1]);
        return 1;
    }



    // repeat until end of card
    //for (int i = 0; i != feof; i++)
    while (fread(buffer, sizeof(uint8_t), BLOCKSIZE, file) || feof(file) == 0)
    {

        // read 512 bytes into a buffer
        //fread(buffer, sizeof(uint8_t), BLOCKSIZE, file);
        // if start of new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if first jpeg
            if (output_pointer != NULL)
            {
                fclose(output_pointer);
            }
            sprintf(filename, "%03i.jpg", a);
            output_pointer = fopen(filename, "w");
            a++;
        }
        if (output_pointer != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, output_pointer);
            //a++;
        }

        else
        {
            // if alreaedy found jpeg
            if (output_pointer != NULL)
            {
                output_pointer = fopen(filename, "w");
                fwrite(buffer, sizeof(buffer), 1, output_pointer);
                //fclose(output_pointer);
            }
        }
    }

    if (output_pointer == NULL)
    {
        fclose(output_pointer);
    }

    if (file == NULL)
    {
        fclose(output_pointer);
    }
    return 0;


}