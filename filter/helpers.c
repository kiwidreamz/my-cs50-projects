#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int int_average = round(average);
            image[i][j].rgbtBlue = int_average;
            image[i][j].rgbtGreen = int_average;
            image[i][j].rgbtRed = int_average;

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
            double sepia_blue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            double sepia_green = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            double sepia_red = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;

            int sepia_blue_int = round(sepia_blue);
            int sepia_green_int = round(sepia_green);
            int sepia_red_int = round(sepia_red);

            if (sepia_red_int >= 256)
            {
                sepia_red_int = 255;
            }
            if (sepia_green_int >= 256)
            {
                sepia_green_int = 255;
            }
            if (sepia_blue_int >= 256)
            {
                sepia_blue_int = 255;
            }

            image[i][j].rgbtBlue = sepia_blue_int;
            image[i][j].rgbtGreen = sepia_green_int;
            image[i][j].rgbtRed = sepia_red_int;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        int current_position = 0;
        for (int j = width - 1; j >= 0; j--, current_position++)
        {
            temp[i][current_position] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    /*
    //int e = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //pos d = [i][j - 1]
            //pos f = [i][j + 1]
            //pos a = [i - 1][j - 1]
            //pos b = [i - 1][j]
            //pos c = [i - 1][j + 1]
            //pos g = [i + 1][j - 1]
            //pos h = [i + 1][j]
            //pos i = [i + 1][j + 1]

            //pos e = [i][j]
            if (i == 0)
            {
                if (j == 0)
                {
                    // f h i / 3

                    double blue = (image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j].rgbtBlue) / 4;
                    double green = (image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j].rgbtGreen) / 4;
                    double red = (image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j].rgbtRed) / 4;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else if (j == width-1)
                {
                    // d g h / 3

                    double blue = (image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i][j].rgbtBlue) / 4;
                    double green = (image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i][j].rgbtGreen) / 4;
                    double red = (image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i][j].rgbtRed) / 4;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else
                {
                    // d f g h i / 5

                    double blue = (image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i][j].rgbtBlue) / 6;
                    double green = (image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i][j].rgbtGreen) / 6;
                    double red = (image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i][j].rgbtRed) / 6;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
            }
            else if (i == height-1)
            {
                if (j == 0)
                {
                    // f b c / 3

                    double blue = (image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue) / 4;
                    double green = (image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen) / 4;
                    double red = (image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed) / 4;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else if (j == width-1)
                {
                    // d a b / 3

                    double blue = (image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j].rgbtBlue) / 4;
                    double green = (image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j].rgbtGreen) / 4;
                    double red = (image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j].rgbtRed) / 4;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else
                {
                    // f b c d a / 5

                    double blue = (image[i][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j-1].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i][j].rgbtBlue) / 6.0;
                    double green = (image[i][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j-1].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i][j].rgbtGreen) / 6.0;
                    double red = (image[i][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j-1].rgbtRed + image[i-1][j-1].rgbtRed + image[i][j].rgbtRed) / 6.0;

                    int blue_int = round(blue);
                    int green_int = round(green);
                    int red_int = round(red);

                    image[i][j].rgbtBlue = blue_int;
                    image[i][j].rgbtGreen = green_int;
                    image[i][j].rgbtRed = red_int;

                }
            }
            else
            {
                if (j == 0)
                {
                    // f h i b c / 5

                    double blue = (image[i][j+1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue) / 6;
                    double green = (image[i][j+1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen) / 6;
                    double red = (image[i][j+1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed) / 6;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else if (j == width-1)
                {
                    // d g h a b/ 5

                    double blue = (image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j].rgbtBlue) / 6;
                    double green = (image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j].rgbtGreen) / 6;
                    double red = (image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j].rgbtRed) / 6;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
                else
                {
                    // d g h a b f i c/ 8

                    double blue = (image[i][j-1].rgbtBlue + image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i][j+1].rgbtBlue + image[i+1][j+1].rgbtBlue + image[i-1][j+1].rgbtBlue + image[i][j].rgbtBlue) / 9;
                    double green = (image[i][j-1].rgbtGreen + image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i][j+1].rgbtGreen + image[i+1][j+1].rgbtGreen + image[i-1][j+1].rgbtGreen + image[i][j].rgbtGreen) / 9;
                    double red = (image[i][j-1].rgbtRed + image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i][j+1].rgbtRed + image[i+1][j+1].rgbtRed + image[i-1][j+1].rgbtRed + image[i][j].rgbtRed) / 9;

                    image[i][j].rgbtBlue = round(blue);
                    image[i][j].rgbtGreen = round(green);
                    image[i][j].rgbtRed = round(red);

                }
            }

        }
    }
    */

    RGBTRIPLE temp[height][width];


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int row_coardinates[] = { i - 1, i, i + 1 };
            int column_coardinates[] = { j - 1, j, j + 1 };
            float total_red = 0;
            float total_green = 0;
            float total_blue = 0;

            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int current_row = row_coardinates[r];
                    int current_column = column_coardinates[c];

                    if (current_row >= 0 && current_row < height && current_column >= 0 && current_column < width)
                    {
                        RGBTRIPLE pixel = image[current_row][current_column];

                        total_red += pixel.rgbtRed;
                        total_green += pixel.rgbtGreen;
                        total_blue += pixel.rgbtBlue;
                        count++;

                    }
                }
            }

            temp[i][j].rgbtRed = round(total_red / count);
            temp[i][j].rgbtGreen = round(total_green / count);
            temp[i][j].rgbtBlue = round(total_blue / count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}
