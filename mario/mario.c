#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // getting user input from 1 to 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // nested loops
    for (int i = 0; i < height; i++)
    {
        // print left-side spaces
        for (int k = height - i; k > 1; k--)
        {
            printf(" ");
        }
        // print first hashes (first part of the pyramid)
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // print two space gap
        printf("  ");

        // print second part of pyramid (same amount of characters as the first hashes)
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        // print new line
        printf("\n");
    }
}