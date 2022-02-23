#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    do
    {
        startSize = get_int("Starting Population Size :");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("Ending Population Size :");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int n;
    for (n = 0; startSize < endSize; n++)
    {
        startSize = startSize + startSize / 3 - startSize / 4;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}