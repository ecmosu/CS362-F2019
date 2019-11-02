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

void unitTestMinion()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set first cards in hand to mine and silver
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
    assert(startCoinCount == (G.coins - 2));
}

void unitTestFeast()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);
    int bonus = 0;

    //Set first cards in hand to mine and silver
    G.hand[G.whoseTurn][0] = feast;

    //Set Choices
    int choice1 = copper;
    
    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Get count of currently discarded cards for player.
    int startCoinCount = G.coins;

    cardEffect(feast, choice1, 0 , 0, &G, 0, &bonus);
    printf("Feast Card Effect Result - Start Coins (%d) == End Coins (%d)\n", startCoinCount, G.coins);

    //The start and end count of coins should not be affected by this card.
    //Playing this action card should simply allow a player to gain a card up to 5.
    assert(startCoinCount == G.coins);
}

void unitTestSeahag()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);
    int bonus = 0;

    //Set first cards in hand to mine and silver
    G.hand[G.whoseTurn][0] = sea_hag;

    //Get count of cards in player 2 hand.
    int startDeckCount = G.deckCount[1];

    cardEffect(sea_hag, 0, 0, 0, &G, 0, &bonus);
    printf("Sea Hag Card Effect Result - Start Cards In P2 Deck (%d) == End Cards In P2 Deck (%d)\n", startDeckCount, G.deckCount[1]);

    //The start and end cards in the deck should be the same in this situation
    //as the player discards one card, and gains another onto their deck.
    assert(startDeckCount == G.deckCount[1]);
}

void unitTestMine()
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
    assert(result == -1); //cardEffect should not allow this set of variables and should return a -1.
}

int main()
{
    unitTestOutpost();
    unitTestMinion();
    unitTestFeast();
    unitTestSeahag();
    unitTestMine();
    printf("ALL TESTS OK\n");
    return 0;
}