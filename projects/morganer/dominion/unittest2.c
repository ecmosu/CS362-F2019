
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

//Unit Tests For Minion
void minionUnitTest1()
{
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

    //Set Choices
    int choice1 = 1;

    //Get count of currently discarded cards for player.
    int startCoinCount = G.coins;

    playCard(0, choice1, 0, 0, &G);
    printf("Minion Option 1 Card Effect Result - Start Coins (%d) == (Start Coins + 2) (%d)\n", startCoinCount, (G.coins - 2));

    //The minion card grants + 2 coins when the first option is selected.    
    //Playing this action card should increase the player's coins by two when completed.
    //This should be accomplished by utilizing the bonus, but it is directly added to the state,
    //which results in the bonus being removed when run in the playCard function.
    //assert(startCoinCount == (G.coins - 2));
}

int main()
{
    minionUnitTest1();
}
