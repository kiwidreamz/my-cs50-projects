#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // initializing changeOwed variable and asking for input of a positive float
    float changeOwed;
    do
    {
        changeOwed = get_float("How much change is owed? ");
    }
    while (changeOwed < 0);

    // printing amount of change owed rounded to 2 decimals
    printf("Change owed: %.2f \n", changeOwed);

    // converting the change owed to cents for easy calculation using only integers
    int centsOwed = round(changeOwed * 100);

    // initializing variables for each of the four possible coins to be given out
    int nbOfQuarters = 0;
    int nbOfDimes = 0;
    int nbOfNickels = 0;
    int nbOfPennies = 0;

    // initializing variables for the modulus (rest of division)
    int a;
    int b;
    int c;

    // conditional statement checking if there are any quarters, how many of them and taking the rest (modulus) into variable a
    if (centsOwed / 25)
    {
        nbOfQuarters = centsOwed / 25;
    }
    a = centsOwed % 25;

    // conditional statement checking if there are any dimes, how many of them and taking the rest (modulus) into variable b
    if (a / 10)
    {
        nbOfDimes = a / 10;
    }
    b = a % 10;

    // conditional statement checking if there are any fives, how many of them and taking the rest (modulus) into variable c
    if (b / 5)
    {
        nbOfNickels = b / 5;
    }
    c = b % 5;

    // conditional statement checking if there are any cents left and how many of them
    if (c / 1)
    {
        nbOfPennies = c / 1;
    }

    // adding up all the coins calculated
    int minimumAmountOfCoins = nbOfQuarters + nbOfDimes + nbOfNickels + nbOfPennies;

    // printing out the final result
    printf("%i \n", minimumAmountOfCoins);

}
