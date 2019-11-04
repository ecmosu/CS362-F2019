#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

//Unit Tests For Tribute
void tributeUnitTest1()
{
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
    G.deck[nextPlayer][G.deckCount[nextPlayer] - 2] = copper;
    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy (&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0,&G, 0, &bonus);
    printf("Tribute Two Treasury Card Result Ending Actions (%d) == Starting Actions (%d)\n", G.numActions, (preG.numActions));
    printf("Tribute Two Treasury Card Result Ending Coins (%d) == Starting Coins + 2 (%d)\n", G.coins, (preG.coins + 2));
    printf("Tribute Two Treasury Card Result Ending Cards (%d) == Starting Cards (%d)\n", G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    printf("Tribute Two Treasury Card Result (%d) == 0\n", result);
}

void tributeUnitTest2()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    G.hand[G.whoseTurn][0] = tribute;

    //Set first card in next player's deck to the same action cards
    G.deck[G.whoseTurn + 1][0] = baron;
    G.deck[G.whoseTurn + 1][1] = baron;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy (&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0,&G, 0, &bonus);
    printf("Tribute Two Action Card Result Ending Actions (%d) == Starting Actions + 2 (%d)\n", G.numActions, (preG.numActions + 2));
    printf("Tribute Two Action Card Result Ending Coins (%d) == Starting Coins (%d)\n", G.coins, (preG.coins));
    printf("Tribute Two Action Card Result Ending Cards (%d) == Starting Cards (%d)\n", G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    printf("Tribute Two Action Card Result (%d) == 0\n", result);
}

void tributeUnitTest3()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    G.hand[G.whoseTurn][0] = tribute;

    printf("Tribute Next Player Discard Count Start:(%d)\n", G.discardCount[G.whoseTurn + 1]);
    printf("Tribute Next Player Deck Count (%d)\n", G.deckCount[G.whoseTurn + 1]);

    //Set first card in next player's deck to the same action cards
    G.discardCount[G.whoseTurn + 1] = 0;
    G.deckCount[G.whoseTurn + 1] = 0;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy (&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0,&G, 0, &bonus);
    printf("Tribute Two No Cards Result Ending Actions (%d) == Starting Actions (%d)\n", G.numActions, (preG.numActions + 2));
    printf("Tribute Two No Cards Result Ending Coins (%d) == Starting Coins (%d)\n", G.coins, (preG.coins));
    printf("Tribute Two No Cards Result Ending Cards (%d) == Starting Cards (%d)\n", G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    printf("Tribute Two No Cards Result (%d) == 0\n", result);
}

void tributeUnitTest4()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    G.hand[G.whoseTurn][0] = tribute;

    printf("Tribute Next Player Discard Count Start:(%d)\n", G.discardCount[G.whoseTurn + 1]);
    printf("Tribute Next Player Deck Count (%d)\n", G.deckCount[G.whoseTurn + 1]);

    //Set first card in next player's deck to the same action cards
    G.discard[G.whoseTurn + 1][0] = copper;
    G.discard[G.whoseTurn + 1][1] = baron;
    G.discardCount[G.whoseTurn + 1] = 2;
    G.deckCount[G.whoseTurn + 1] = 0;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy (&preG, &G, sizeof(struct gameState));

    int bonus = 0;
    int result = cardEffect(tribute, 1, 0, 0,&G, 0, &bonus);
    printf("Tribute Two No Cards Result Ending Actions (%d) == Starting Actions (%d)\n", G.numActions, (preG.numActions + 2));
    printf("Tribute Two No Cards Result Ending Coins (%d) == Starting Coins (%d)\n", G.coins, (preG.coins));
    printf("Tribute Two No Cards Result Ending Cards (%d) == Starting Cards (%d)\n", G.handCount[G.whoseTurn], (preG.handCount[G.whoseTurn]));
    printf("Tribute Two No Cards Result (%d) == 0\n", result);
}

int main()
{
    tributeUnitTest1();
    tributeUnitTest2();
    tributeUnitTest3();
    tributeUnitTest4();
}