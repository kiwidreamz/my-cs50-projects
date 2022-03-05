#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string

    // initializing variables for later use
    int getPointsByASCII(int ascii);
    int stringLength = strlen(word);
    int asciiValue;
    int toAdd;

    // initializing the wordScore at 0 because it was giving me negative values otherwise
    int wordScore = 0;

    // looping through every character of each word
    for (int i = 0; i < stringLength; i++)
    {
        asciiValue = word[i];

        // turning everything into lowercase by adding 32 for each capital letter ascii value
        if (asciiValue >= 65 && asciiValue <= 90)
        {
            asciiValue = asciiValue + 32;
        }

        // calling my getPoints function by passing it the ascii value of each lowercase character
        toAdd = getPointsByASCII(asciiValue);

        // adding the scores up
        wordScore = wordScore + toAdd;
    }
    // returning the score
    return wordScore;

}

// this function takes each ascii character and returns a score value to be added
int getPointsByASCII(int ascii)
{
    // couple if statements to return 0 for every punctuation sign or any character that isn't a letter per say
    if (ascii < 65)
    {
        return 0;
    }
    else if (ascii >= 91 && ascii < 97)
    {
        return 0;
    }
    else if (ascii >= 123)
    {
        return 0;
    }
    else
    {
        // switch statement with every ascii from a to z returning the appropriate score for each letter
        switch (ascii)
        {
            case 97:
                return 1;
                break;
            case 98:
                return 3;
                break;
            case 99:
                return 3;
                break;
            case 100:
                return 2;
                break;
            case 101:
                return 1;
                break;
            case 102:
                return 4;
                break;
            case 103:
                return 2;
                break;
            case 104:
                return 4;
                break;
            case 105:
                return 1;
                break;
            case 106:
                return 8;
                break;
            case 107:
                return 5;
                break;
            case 108:
                return 1;
                break;
            case 109:
                return 3;
                break;
            case 110:
                return 1;
                break;
            case 111:
                return 1;
                break;
            case 112:
                return 3;
                break;
            case 113:
                return 10;
                break;
            case 114:
                return 1;
                break;
            case 115:
                return 1;
                break;
            case 116:
                return 1;
                break;
            case 117:
                return 1;
                break;
            case 118:
                return 4;
                break;
            case 119:
                return 4;
                break;
            case 120:
                return 8;
                break;
            case 121:
                return 4;
                break;
            case 122:
                return 10;
                break;
        }
        // switch needs a return returning 0 in case the value is anything other than an ascii value
        return 0;
    }
}
