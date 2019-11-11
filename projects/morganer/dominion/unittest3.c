#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//Unit Tests For Ambassador
void ambassadorUnitTest1()
{
    char *messagePrefix = "AMBASSADOR UT 1 - Return 1 Copy Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = ambassador;
    G.hand[G.whoseTurn][1] = copper;
    G.hand[G.whoseTurn][2] = copper;
    G.hand[G.whoseTurn][3] = copper;
    G.hand[G.whoseTurn][4] = copper;
    G.hand[G.whoseTurn][5] = copper;
    G.handCount[G.whoseTurn] = 6;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    //Set Choices
    int choice1 = 2;
    int choice2 = 1;

    int result = playCard(0, choice1, choice2, 0, &G);
    assert(preG.supplyCount[copper] == (G.supplyCount[copper]), "%s - Start Copper Supply (%d) == (End Copper Supply) (1 Card Returned 1 Card Given To Player 2) (%d)\n", messagePrefix, preG.supplyCount[copper], (G.supplyCount[copper]));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void ambassadorUnitTest2()
{
    char *messagePrefix = "AMBASSADOR UT 2 - Return 2 Copies Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = ambassador;
    G.hand[G.whoseTurn][1] = copper;
    G.hand[G.whoseTurn][2] = copper;
    G.hand[G.whoseTurn][3] = copper;
    G.hand[G.whoseTurn][4] = copper;
    G.hand[G.whoseTurn][5] = copper;
    G.handCount[G.whoseTurn] = 6;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    //Set Choices
    int choice1 = 2;
    int choice2 = 2;

    int result = playCard(0, choice1, choice2, 0, &G);
    assert(preG.supplyCount[copper] == (G.supplyCount[copper] - 1), "%s - Start Copper Supply (%d) == (End Copper Supply - 1) (2 Cards Returned 1 Card Given To Player 2) (%d)\n", messagePrefix, preG.supplyCount[copper], (G.supplyCount[copper] - 1));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void ambassadorUnitTest3()
{
    char *messagePrefix = "AMBASSADOR UT 3 - Return -1 Copies Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = ambassador;
    G.hand[G.whoseTurn][1] = copper;
    G.hand[G.whoseTurn][2] = copper;
    G.hand[G.whoseTurn][3] = copper;
    G.hand[G.whoseTurn][4] = copper;
    G.hand[G.whoseTurn][5] = copper;
    G.handCount[G.whoseTurn] = 6;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    //Set Choices
    int choice1 = 2;
    int choice2 = -1;

    int result = playCard(0, choice1, choice2, 0, &G);
    assert(preG.supplyCount[copper] == (G.supplyCount[copper]), "%s - Start Copper Supply (%d) == (End Copper Supply) (Erroneous Selection, No Change) (%d)\n", messagePrefix, preG.supplyCount[copper], (G.supplyCount[copper]));
    assert(result == -1, "%s - (%d) == -1\n", messagePrefix, result);
}

int main()
{
    ambassadorUnitTest1();
    ambassadorUnitTest2();
    ambassadorUnitTest3();
}