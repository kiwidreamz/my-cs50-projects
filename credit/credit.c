#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>


// Four main steps :
// A - input
// B - check validity of card number (through Luhn's)
// C - check which provider
// D - output


int main(void)
{

    string output = "Not yet known";
    bool luhnValidity = false;
    bool digitValid = false;

    // input
    long cardNumber;

    do
    {
        cardNumber = get_long("Card Number: ");
    }
    while (cardNumber < 0);

    // B
    // check if there are 13, 15 or 16 digits
    int digits = floor(log10(labs(cardNumber))) + 1;

    if (digits == 13 || digits == 15 || digits == 16)
    {
        digitValid = true;
    }
    else
    {
        digitValid = false;
    }

    // Luhn's
    // get all numbers that need to be multiplied by 2
    long cc = cardNumber / 10;
    long nMby2 = 0;
    while (cc != 0)
    {
        long last = cc % 10;
        nMby2 = nMby2 * 10 + last;
        cc = cc / 100;
    }
    //printf("to multiply by 2: %li\n", nMby2);


    // get all other numbers
    long cc2 = cardNumber;
    long nOthers = 0;
    while (cc2 != 0)
    {
        long last2 = cc2 % 10;
        nOthers = nOthers * 10 + last2;
        cc2 = cc2 / 100;
    }
    //printf("other numbers: %li\n", nOthers);

    // add up every digit from other numbers
    int toAdd = nOthers;
    int remaindeR;
    int sumofOthers;
    while (toAdd != 0)
    {
        remaindeR = toAdd % 10;
        sumofOthers = sumofOthers + remaindeR;
        toAdd = toAdd / 10;
    }
    //printf("sum of other numbers: %i\n", sumofOthers);

    // adding up the digits that need to be multiplied by two, switch statement decides which integer to add depending on the digit
    int toAdd2 = nMby2;
    int remainder2, remaindeR2;
    int sumofNumbersby2;
    while (toAdd2 != 0)
    {
        switch (toAdd2 % 10)
        {
            case 0:
                remainder2 = 0;
                break;
            case 1:
                remainder2 = 2;
                break;
            case 2:
                remainder2 = 4;
                break;
            case 3:
                remainder2 = 6;
                break;
            case 4:
                remainder2 = 8;
                break;
            case 5:
                remainder2 = 1;
                break;
            case 6:
                remainder2 = 3;
                break;
            case 7:
                remainder2 = 5;
                break;
            case 8:
                remainder2 = 7;
                break;
            case 9:
                remainder2 = 9;
                break;
        }
        remaindeR2 = remainder2;

        sumofNumbersby2 = sumofNumbersby2 + remaindeR2;
        toAdd2 = toAdd2 / 10;
    }
    //printf("sum of numbers by 2: %i\n", sumofNumbersby2);

    // add up both sums
    int totalSumOfBothSetsOfDigits = sumofNumbersby2 + sumofOthers;

    // check if last digit is 0
    if (totalSumOfBothSetsOfDigits % 10 != 0)
    {
        luhnValidity = false;
    }
    else
    {
        luhnValidity = true;
    }


    //C

    // get first digit
    long input = cardNumber;
    long firstDig = input;

    while (firstDig >= 10)
    {
        firstDig = firstDig / 10;
    }

    // get first two digits
    long input2 = cardNumber;
    long firstTwo = input2;

    while (firstTwo >= 100)
    {
        firstTwo = firstTwo / 10;
    }

    //printf("first digit: %li\n", firstDig);
    //printf("first 2 digits: %li\n", firstTwo);


    // check which provider
    string cardType;

    // if 15 digits, check first two are 34 or 37 (AMEX)
    if ((digits == 15 && firstTwo == 34) || (digits == 15 && firstTwo == 37))
    {
        cardType = "AMEX";
    }


    // if 13 digits, check first is 4 (VISA)
    else if (digits == 13 && firstDig == 4)
    {
        cardType = "VISA";
    }


    // if 16 digits, check first is 4 (VISA)
    else if (digits == 16 && firstDig == 4)
    {
        cardType = "VISA";
    }


    // if 16, check first two are 51 or 52 or 53 or 54 or 55 (MASTERCARD)
    else if ((digits == 16 && firstTwo == 51) ||
             (digits == 16 && firstTwo == 52) ||
             (digits == 16 && firstTwo == 53) ||
             (digits == 16 && firstTwo == 54) ||
             (digits == 16 && firstTwo == 55))
    {
        cardType = "MASTERCARD";
    }

    // else (INVALID)
    else
    {
        cardType = "INVALID";
    }


    //D
    // output

    if (digitValid == false)
    {
        output = "INVALID";
    }
    else if (luhnValidity == false)
    {
        output = "INVALID";

    }
    else if (luhnValidity == true)
    {
        output = cardType;
    }

    printf("%s\n", output);


}