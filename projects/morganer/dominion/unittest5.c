#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

//Unit Tests For Mine
void mineUnitTest1()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);
    int bonus = 0;

    //Set first cards in hand to mine and silver
    G.hand[G.whoseTurn][0] = mine;
    G.hand[G.whoseTurn][1] = silver;

    int choice1 = 1;          //Card in hand to trash (silver)
    int choice2 = adventurer; //Card to gain (THIS SHOULD NOT BE ALLOWED)

    int result = cardEffect(mine, choice1, choice2, 0, &G, 0, &bonus);
    printf("Mine Card Effect Result == %d\n", result);
}

int main()
{
    mineUnitTest1();
}