#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

int calculate26(int letter);

int main(int argc, string argv[])
{

    // initializing the success as false
    bool success = false;
    //bool letters_success = false;
    //bool success_26 = false;
    //bool repeated_success = true;

    int repeated = 0;

    // if contains only 2 arguments
    if (argc == 2)
    {
        int string_length = strlen(argv[1]);
        // if second argument length is 26
        if (string_length == 26)
        {
            // if second argument contains only alphas
            for (int i = 0; i < string_length; i++)
            {
                if (isalpha(argv[1][i]))
                {
                    // must not contain repeated characters
                    for (int j = 0; j < string_length; j++)
                    {
                        for (int k = j + 1; k < string_length; k++)
                        {
                            if (tolower(argv[1][j]) == tolower(argv[1][k]))
                            {
                                repeated++;
                                printf("Key must not contain repeated characters.\n");
                                return 1;
                                break;
                            }
                            else
                            {
                                success = true;
                            }
                        }
                    }
                }
                else
                {
                    printf("Key must only contain alphanumeric characters.\n");
                    return 1;
                    break;
                }

            }
        }
        else if (string_length != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }


    else if (argc > 2)
    {
        success = false;
        printf("Error, too many arguments\n");
        return 1;
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // if key satisfactory, take input
    if (repeated == 0)
    {
        string plaintext = get_string("plaintext: ");
        int plain_length = strlen(plaintext);

        // print ciphertext and wait for the encrypted characters
        printf("ciphertext: ");

        for (int w = 0; w < plain_length; w++)
        {

            // if lowercase, go get the letter at equivalent position in key
            if (isalpha(plaintext[w]) && isupper(plaintext[w]))
            {

                int upper_position = (plaintext[w] - 65);
                printf("%c", toupper(argv[1][upper_position]));

            }

            // if uppercase, go get the letter at equivalent position in key
            else if (isalpha(plaintext[w]) && islower(plaintext[w]))
            {
                int lower_position = (plaintext[w] - 97);
                printf("%c", tolower(argv[1][lower_position]));
            }

            // any non alphabetic character stays the same
            else
            {

                printf("%c", plaintext[w]);

            }


        }

        // new line
        printf("\n");
        return 0;
    }

}



