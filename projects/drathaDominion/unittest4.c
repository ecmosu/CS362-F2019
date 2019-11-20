#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//Unit Tests For Tribute
void tributeUnitTest1()
{    
    char* messagePrefix = "TRIBUTE UT 1 - Two Treasury Card Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    int nextPlayer = G.whoseTurn + 1;
    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to treasure cards
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = copper;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = silver;
    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);

    assert(G.numActions == (preG.numActions), "%s - Ending Actions (%d) == Starting Actions (%d)\n", messagePrefix, G.numActions, (preG.numActions));
    assert(G.coins == (preG.coins + 4), "%s - Ending Coins (%d) == Starting Coins + 4 (%d)\n", messagePrefix, G.coins, (preG.coins + 4));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn]), "%s - Ending Cards (%d) == Starting Cards (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void tributeUnitTest2()
{
    char* messagePrefix = "TRIBUTE UT 2 - Two Action Card Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    int nextPlayer = G.whoseTurn + 1;
    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to the same action cards
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = baron;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = mine; //This card currently won't be hit because of bug in code decrementing the deckCount multiple times.
    //G.deck[nextPlayer][G.deckCount[nextPlayer] - 3] = mine; //This would address but is not accurate.

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);

    assert(G.numActions == (preG.numActions + 4), "%s - Ending Actions (%d) == Starting Actions + 4 (%d)\n", messagePrefix, G.numActions, (preG.numActions + 4));
    assert(G.coins == (preG.coins), "%s - Ending Coins (%d) == Starting Coins (%d)\n", messagePrefix, G.coins, (preG.coins));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn]), "%s - Ending Cards (%d) == Starting Cards (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void tributeUnitTest3()
{
    char* messagePrefix = "TRIBUTE UT 3 - Two Victory Card Result";
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    int nextPlayer = G.whoseTurn + 1;
    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to victory cards
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 1] = province;
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = duchy; //This card currently won't be hit because of bug in code decrementing the deckCount multiple times.
    //G.deck[nextPlayer][G.deckCount[nextPlayer] - 3] = duchy; //This would address but is not accurate.
    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);

    assert(G.numActions == (preG.numActions), "%s - Ending Actions (%d) == Starting Actions (%d)\n", messagePrefix, G.numActions, (preG.numActions));
    assert(G.coins == (preG.coins), "%s - Ending Coins (%d) == Starting Coins (%d)\n", messagePrefix, G.coins, (preG.coins));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn] + 4), "%s - Ending Cards (%d) == Starting Cards + 4 (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn] + 4));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void tributeUnitTest4()
{
    char* messagePrefix = "TRIBUTE UT 4 - No Cards Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to the same action cards
    G.discardCount[G.whoseTurn + 1] = 0;
    G.deckCount[G.whoseTurn + 1] = 0;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);
    assert(G.numActions == (preG.numActions), "%s - Ending Actions (%d) == Starting Actions (%d)\n", messagePrefix, G.numActions, (preG.numActions));
    assert(G.coins == (preG.coins), "%s - Ending Coins (%d) == Starting Coins (%d)\n", messagePrefix, G.coins, (preG.coins));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn]), "%s - Ending Cards (%d) == Starting Cards (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void tributeUnitTest5()
{
    char* messagePrefix = "TRIBUTE UT 5 - Treasure Discard Pile Only Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to the same action cards
    G.discard[G.whoseTurn + 1][0] = copper;
    G.discard[G.whoseTurn + 1][1] = silver;
    G.discardCount[G.whoseTurn + 1] = 2;
    G.deckCount[G.whoseTurn + 1] = 0;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0, &G, 0, &bonus);
    assert(G.numActions == (preG.numActions), "%s - Ending Actions (%d) == Starting Actions (%d)\n", messagePrefix, G.numActions, (preG.numActions));
    assert(G.coins == (preG.coins + 4), "%s - Ending Coins (%d) == Starting Coins + 4 (%d)\n", messagePrefix, G.coins, (preG.coins + 4));
    assert(G.handCount[G.whoseTurn] == (preG.handCount[G.whoseTurn]), "%s - Ending Cards (%d) == Starting Cards (%d)\n", messagePrefix, G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

int main()
{
    tributeUnitTest1();
    tributeUnitTest2();
    tributeUnitTest3();
    tributeUnitTest4();
    tributeUnitTest5();
}