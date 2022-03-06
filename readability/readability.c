#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    // get input from user
    string text;
    text = get_string("Text: ");

    int textLength = strlen(text);

    // initializing variables at 0 except words since the last word doesn't end with a space
    int words = 1;
    int letters = 0;
    int sentences = 0;

    // for loop incrementing our three variables
    for (int i = 0; i < textLength; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            letters++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }


    }

    // initializing a few variables needed for computation of index
    float lettersPer100 = 0;
    float multiplier = 0;
    float sentencesPer100 = 0;
    float index = 0;
    int answer = 0;

    // computing per 100 word values
    multiplier = 100.0 / words;

    lettersPer100 = multiplier * letters;
    sentencesPer100 = multiplier * sentences;

    // Coleman-Liau formula
    index = 0.0588 * lettersPer100 - 0.293 * sentencesPer100 - 15.8;

    answer = round(index);

    // output

    if (answer < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (answer >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", answer);
    }

}
