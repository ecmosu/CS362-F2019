#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

//Unit Tests For Ambassador
void ambassadorUnitTest1()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = ambassador;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Set Choices
    int choice1 = 1;
    int choice2 = 5;

    int result = playCard(0, choice1, choice2, 0, &G);
    printf("Ambassador Result (%d)\n", result);
}

int main()
{
    ambassadorUnitTest1();
}