#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

//Unit Tests For Minion
void minionUnitTest1()
{
    char *messagePrefix = "MINION UT 1 - Gain Gold Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = minion;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int result = playCard(0, 1, 0, 0, &G);

    //The minion card grants + 2 coins when the first option is selected.    
    //Playing this action card should increase the player's coins by two when completed.
    //This should be accomplished by utilizing the bonus, but it is directly added to the state,
    //which results in the bonus being removed when run in the playCard function.
    assert(preG.coins == (G.coins - 2), "%s - Start Coins (%d) == (End Coins - 2) (%d)\n", messagePrefix, preG.coins, (G.coins - 2));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

void minionUnitTest2()
{
    char *messagePrefix = "MINION UT 2 - Card Effect Result";

    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to minion
    G.hand[G.whoseTurn][0] = minion;
    G.handCount[G.whoseTurn] = 1;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Save current game state
    struct gameState preG;
    memcpy(&preG, &G, sizeof(struct gameState));

    int result = playCard(0, 0, 1, 0, &G);

    //The minion card grants + 2 coins when the first option is selected.    
    //Playing this action card should increase the player's coins by two when completed.
    //This should be accomplished by utilizing the bonus, but it is directly added to the state,
    //which results in the bonus being removed when run in the playCard function.
    assert(preG.deckCount[preG.whoseTurn] == (G.deckCount[G.whoseTurn] + 4), "%s - Start Deck Count (%d) == (End Deck Count + 4) (%d)\n", messagePrefix, preG.deckCount[preG.whoseTurn], (G.deckCount[G.whoseTurn] + 4));
    assert(preG.discardCount[preG.whoseTurn] == (G.discardCount[G.whoseTurn] - 1), "%s - Start Discard Count (%d) == (End Discard Count - 1) (%d)\n", messagePrefix, preG.discardCount[preG.whoseTurn], (G.discardCount[G.whoseTurn] - 1));
    assert(preG.playedCardCount == G.playedCardCount, "%s - Start Played Count (%d) == (End Played Count) (%d)\n", messagePrefix, preG.playedCardCount, (G.playedCardCount));
    assert(result == 0, "%s - (%d) == 0\n", messagePrefix, result);
}

int main()
{
    minionUnitTest1();
    minionUnitTest2();
}
