#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "tinymt32.c"
#include "tinymt32.h"

int getRandomNumber();
int* getPlayerRolls(int amount);
int displayResults(int amount);
void displayRandomNumber();
int calculateSuccess(int *results, int amount, int difficulty);
int calculateOne(int *results, int amount);
void calculateAll(int *results, int amount, int difficulty);

int main()
{
    int dice;
    int difficulty;
    int *results;

    srand(time(NULL));

    do
    {
    //Inquiry for amount of d10's
    printf("Enter amount of d10's: ");
    //scanf("%d", &dice);
    dice = getInput();
    printf("%d \n\n", dice);


    //Inquiry for Difficulty
    printf("Enter Difficulty: ");
    //scanf("%d", &difficulty);
    difficulty = getInput();
    printf("%d \n\n", difficulty);

    results = displayResults(dice);

    calculateAll(results, dice, difficulty);
    printf("\n_______________________\n");
    }while(1==1);

    return 0;
}

int getInput()
{
    int userInput, properInput = 0;

    do
    {

        if(scanf("%i", &userInput)== 0)
        {
            printf("\nI'm sorry, but you did not enter a number. Please try again.\n\n");
            printf("Enter Value: ");
            while((userInput = getchar()) != '\n' && userInput != EOF);

        }
        else
        {
            properInput = 1;
        }

    }while(properInput == 0);

    return userInput;
}

// Generates a random number
int getRandomNumber()
{
    tinymt32_t tinymt;
    tinymt32_init(&tinymt, rand());
    return tinymt32_generate_uint32(&tinymt)%10+1;
    //return rand() % 10+1;
}

// Collects the rolls the player makes
// as an array
int* getPlayerRolls(int amount)
{
    int* rolls = calloc(amount, sizeof(int));
    int i;

    for(i = 0; amount > i; i++)
    {
        rolls[i] = getRandomNumber();
    }

    return rolls;
}

// Displays the results of the rolls
int displayResults(int amount)
{
    int *results;

    //Initialize the results
    results = getPlayerRolls(amount);

    int i;

    int resultsLength = sizeof(results);

    //Print up all the rolls
    printf("Full Results: ");
    for(i=0; i < amount; i++)
    {
        printf("%d, ", results[i]);
    }
    printf("\n\n");

    return results;
}

// Checks for successes
// Successes are defined as any number
// greater than or equal to the Difficulty
int calculateSuccess(int *results, int amount, int difficulty)
{
    int i, successCount = 0;

    for(i = 0; i < amount; i++)
    {
        if(results[i] >= difficulty)
        {
            successCount++;
        }
    }
    printf("Amount of Successes: %i\n", successCount);
    return successCount;
}

//Tally up the one's
int calculateOne(int *results, int amount)
{
    int i, oneCount = 0;

    for(i = 0; i < amount; i++)
    {
        if(results[i] == 1)
        {
            oneCount++;
        }
    }
    printf("Amount of 1's: %i\n", oneCount);
    return oneCount;
}

void calculateAll(int *results, int amount, int difficulty)
{
    int successes, ones;

    successes = calculateSuccess(results, amount, difficulty);
    ones = calculateOne(results, amount);

    printf("Total amount of successes: %i\n", (successes-ones));
    botchDetection(successes, ones, (successes-ones));

}

// Within the rules, 1's cancel out
// successes. If the player rolls
// no successes and one "1", then
// it is considered a botch
void botchDetection(int successes, int ones, int totalSuccesses)
{
    if(ones > successes)
        printf("\nBOTCH!\n");
    else if(successes == 0 & ones == 0)
        printf("\nFAILURE!\n");
    else if(totalSuccesses > 0)
        printf("\nSUCCESS!\n");
}
