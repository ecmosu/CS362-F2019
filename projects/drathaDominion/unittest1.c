#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//Unit Tests For Baron
void baronUnitTest1()
{
    char *messagePrefix = "BARON UT 1 - Discard Estate Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = estate;
    G.hand[G.whoseTurn][2] = copper;
    G.handCount[G.whoseTurn] = 3;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    int estateCountBefore = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountBefore++;
    }

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(baron, 1, 0, 0, &G, 0, &bonus);

    int estateCountAfter = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountAfter++;
    }

    assert(G.numBuys == (preG.numBuys + 1), "%s - End Num Buys (%d) == Start Num Buys + 1 (%d)\n", messagePrefix, G.numBuys, (preG.numBuys + 1));
    assert(G.coins == (preG.coins + 4), "%s - End Num Coins (%d) == Start Num Coins + 4 (%d)\n", messagePrefix, G.coins, (preG.coins + 4));
    assert(estateCountAfter == (estateCountBefore - 1), "%s - Ending Estate Cards (%d) == Starting Estate Cards - 1 (%d)\n", messagePrefix, estateCountAfter, (estateCountBefore - 1));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

//Unit Tests For Baron
void baronUnitTest2()
{
    char *messagePrefix = "BARON UT 2 - Discard Estate None In Hand Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }
    G.handCount[G.whoseTurn] = 0;

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.hand[G.whoseTurn][1] = copper;
    G.hand[G.whoseTurn][2] = copper;
    G.handCount[G.whoseTurn] = 3;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    int estateCountBefore = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountBefore++;
    }

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(baron, 1, 0, 0, &G, 0, &bonus);

    int estateCountAfter = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountAfter++;
    }

    assert(G.numBuys == (preG.numBuys + 1), "%s - End Num Buys (%d) == Start Num Buys + 1 (%d)\n", messagePrefix, G.numBuys, (preG.numBuys + 1));
    assert(G.coins == (preG.coins), "%s - End Num Coins (%d) == Start Num Coins (%d)\n", messagePrefix, G.coins, (preG.coins));
    //These two should be accurate though an existing bug at line 36 does not add to hand, but instead adds to discard
    assert(estateCountAfter == (estateCountBefore), "%s - Ending Estate Cards In Hand (%d) == Starting Estate Cards In Hand (%d)\n", messagePrefix, estateCountAfter, (estateCountBefore));
    assert(G.discardCount[G.whoseTurn] == (preG.discardCount[preG.whoseTurn] + 1), "%s - Ending Discard Cards (%d) == Starting Discard Cards + 1 (%d)\n", messagePrefix, G.discardCount[G.whoseTurn], (preG.discardCount[preG.whoseTurn] + 1));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void baronUnitTest3()
{
    char *messagePrefix = "BARON UT 3 - Gain Estate Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to baron card
    G.hand[G.whoseTurn][0] = baron;
    G.handCount[G.whoseTurn] = 1;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    int estateCountBefore = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountBefore++;
    }

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(baron, 0, 0, 0, &G, 0, &bonus);

    int estateCountAfter = 0;
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if (G.hand[G.whoseTurn][i] == estate)
            estateCountAfter++;
    }

    assert(G.numBuys == (preG.numBuys + 1), "%s - End Num Buys (%d) == Start Num Buys + 1 (%d)\n", messagePrefix, G.numBuys, (preG.numBuys + 1));
    assert(estateCountAfter == (estateCountBefore), "%s - Ending Estate Cards In Hand (%d) == Starting Estate Cards In Hand (%d)\n", messagePrefix, estateCountAfter, (estateCountBefore));
    assert(G.discardCount[G.whoseTurn] == (preG.discardCount[preG.whoseTurn] + 1), "%s - Ending Discard Cards (%d) == Starting Discard Cards + 1 (%d)\n", messagePrefix, G.discardCount[G.whoseTurn], (preG.discardCount[preG.whoseTurn] + 1));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

int main()
{
    baronUnitTest1();
    baronUnitTest2();
    baronUnitTest3();
}