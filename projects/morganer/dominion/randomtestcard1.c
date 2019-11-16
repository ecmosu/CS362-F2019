#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffects.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

//Random Tests For Baron
int baronRandomTester()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set Randomizor Stream
    SelectStream(2);

    //Set Estate Supply Count
    G.supplyCount[estate] = round(Random() * 2);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }

    //Set first card in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.handCount[G.whoseTurn] = 1;

    //Randomize number of additional cards in hand other than Baron between 0 and 5
    int numCards = round(Random() * 5);
    for(int numCard = 1; numCard <= numCards; numCard++)
    {
        //Insert random card between 0 (curse) and 26 (treasure_map) 
        G.hand[G.whoseTurn][numCard] = round(Random() * treasure_map);
    }
    
    G.handCount[G.whoseTurn] += numCards;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Randomize card choice
    int choice1 = round(Random() * 1);
    int result = baronCardEffect(&G, G.whoseTurn, choice1);
    //printf("Baron - Number of Cards: %d - Choice 1 Selection: %d - Result: %d\n", G.handCount[G.whoseTurn], choice1, result);
    return result;
}

int main()
{
    SelectStream(2);
    PutSeed((long)1);

    int numSuccess = 0;
    int totalTests = 1000;
    for(int numTest = 1; numTest <= totalTests; numTest++)
    {
        if(baronRandomTester() == 0)
        {
            numSuccess++;
        }
    }

    printf("Baron - Number of Successful Tests: %d out of %d\n", numSuccess, totalTests);
}