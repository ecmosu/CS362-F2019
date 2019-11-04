#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

//Unit Tests For Baron
void baronUnitTest1()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);


    int startBuys = G.numBuys;
    int bonus = 0;
    cardEffect(baron, 1, 0, 0,&G, 0, &bonus);

    printf("Baron Card Effect Result - End Num Buys (%d) == Start Num Buys + 1 (%d)\n", G.numBuys, (startBuys + 1));
}

void baronUnitTest2()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);


    int startBuys = G.numBuys;
    int bonus = 0;
    cardEffect(baron, 0, 0, 0,&G, 0, &bonus);

    printf("Baron Card Effect Result - End Num Buys (%d) == Start Num Buys + 1 (%d)\n", G.numBuys, (startBuys + 1));
}

int main()
{
    baronUnitTest1();
    baronUnitTest2();
}
