#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // initializing the success as false
    bool success = false;

    // if one argument containing only digits taken, success true
    if (argc == 2)
    {
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
                success = true;
            }
            else
            {
                success = false;
            }
        }

    }
    else
    {
        success = false;
    }

    // continue to text encryption if argument taken satisfactory
    if (success == true)
    {

        // take plaintext input
        string plaintext;
        plaintext = get_string("plaintext: ");

        // print ciphertext and wait for the encrypted characters
        printf("ciphertext: ");

        // turn argument key into integer
        int key = atoi(argv[1]);

        // initialize variables for later use
        int cipher_position;
        int a;
        char ch;

        int plaintext_length = strlen(plaintext);

        // looping through every character in plaintext
        for (int j = 0; j < plaintext_length; j++)
        {
            a = plaintext[j];

            // lowercase characters
            if (a >= 97 && a <= 122)
            {
                cipher_position = ((a - 97) + key) % 26;
                ch = 97 + cipher_position;
            }

            //uppercase characters
            else if (a >= 65 && a <= 90)
            {
                cipher_position = ((a - 65) + key) % 26;
                ch = 65 + cipher_position;
            }

            // spaces remain spaces
            else if (a == 32)
            {
                ch = 32;
            }

            // every other character remain as they are
            else
            {
                ch = a;
            }

            // print every encrypted character one by one
            printf("%c", ch);

        }

        // new line
        printf("\n");

    }

    // if argument not satisfactory, print usage information and return 1
    else if (success == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

}