#include "dominion.h"
#include "dominion_helpers.h"
#include "cardEffects.h"
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rngs.h"

//Random Tests For Tribute
int tributeRandomTester()
{
    //Set Card Array
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    //Setup Game State
    struct gameState G;
    initializeGame(2, k, 1, &G);

    //Set Randomizor Stream
    SelectStream(2);

    //Reset Hand
    for (int i = 0; i < G.handCount[G.whoseTurn]; i++)
    {
        G.hand[G.whoseTurn][i] = -1;
    }

    //Set first card in hand to tribute card
    G.hand[G.whoseTurn][0] = tribute;
    G.handCount[G.whoseTurn] = 1;

    //Randomize next player's deck between 0 to 5.
    G.deckCount[G.whoseTurn + 1] = round(Random() * 5);
    for(int numCard = 0; numCard < G.deckCount[G.whoseTurn + 1]; numCard++)
    {
        //Insert random card between 0 (curse) and 26 (treasure_map) 
        G.deck[G.whoseTurn + 1][numCard] = round(Random() * treasure_map);
    }

    //Randomize next player's discard pile between 0 to 5.
    G.discardCount[G.whoseTurn + 1] = round(Random() * 5);
    for(int numCard = 0; numCard < G.discardCount[G.whoseTurn + 1]; numCard++)
    {
        //Insert random card between 0 (curse) and 26 (treasure_map) 
        G.discard[G.whoseTurn + 1][numCard] = round(Random() * treasure_map);
    }

    //Randomize number of additional cards in hand other than Tribute between 0 and 5
    int numCards = round(Random() * 5);
    for(int numCard = 1; numCard <= numCards; numCard++)
    {
        //Insert random card between 0 (curse) and 26 (treasure_map) 
        G.hand[G.whoseTurn][numCard] = round(Random() * treasure_map);
    }
    
    G.handCount[G.whoseTurn] += numCards;

    //Update coins to account for potential impact to changing first card.
    updateCoins(0, &G, 0);

    //Randomize card choice
    int result = tributeCardEffect(&G, G.whoseTurn, G.whoseTurn + 1);
    //printf("Tribute - Number of Cards: %d - Result: %d\n", G.handCount[G.whoseTurn], result);
    return result;
}

int main()
{
    SelectStream(2);
    PutSeed((long)1);

    int numSuccess = 0;
    int totalTests = 1000;
    for(int numTest = 1; numTest <= totalTests; numTest++)
    {
        if(tributeRandomTester() == 0)
        {
            numSuccess++;
        }
    }

    printf("Tribute - Number of Successful Tests: %d out of %d\n", numSuccess, totalTests);
}