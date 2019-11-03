
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

void unitTestOutpost()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to mine and silver
    G.hand[G.whoseTurn][0] = outpost;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    int currentPlayerTurn = G.whoseTurn;
    printf("Outpost Card Effect Result - Current Player Turn (%d)\n", currentPlayerTurn);
    playCard(0, 0, 0, 0, &G);
    printf("Outpost Card Effect Result - Outposts Played == 1 (%d)\n", G.outpostPlayed);
    endTurn(&G);

    int nextPlayerTurn = G.whoseTurn;
    printf("Outpost Card Effect Result - Next Player Turn (%d)\n", nextPlayerTurn);

    //When an Outpost card is played it allows the player to take an extra turn after their current turn is over.
    //The current implementation of the Outpost card increments a flag tracking if the card was played, but does
    //not currently grant the player an extra turn.
    assert(currentPlayerTurn == nextPlayerTurn);
}

int main()
{
    unitTestOutpost();
}
