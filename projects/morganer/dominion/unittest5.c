#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//Unit Tests For Mine
void mineUnitTest1()
{
    char* messagePrefix = "MINE UT 1 - Mine Card Adventurer Selection Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to mine and silver
    G.hand[G.whoseTurn][0] = mine;
    G.hand[G.whoseTurn][1] = silver;

    int choice1 = 1;          //Card in hand to trash (silver)
    int choice2 = adventurer; //Card to gain (THIS SHOULD NOT BE ALLOWED)

    int mineCountBefore = 0;
    for(int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if(G.hand[G.whoseTurn][i] == mine) mineCountBefore++;
    }

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(mine, choice1, choice2, 0, &G, 0, &bonus);

    int mineCountAfter = 0;
    for(int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        if(G.hand[G.whoseTurn][i] == mine) mineCountAfter++;
    }

    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn] - 1), "%s - Ending Cards (%d) == Starting Cards - 1 (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn] - 1));
    assert(mineCountAfter == (mineCountBefore - 1), "%s - Ending Mine Cards (%d) == Starting Mine Cards - 1 (%d)\n", messagePrefix, mineCountAfter, (mineCountBefore - 1));
    assert(result == -1, "%s - (%d) == -1 - Should not allow player to gain adventurer card.\n", messagePrefix, result);
}

int main()
{
    mineUnitTest1();
}