#include "cardEffects.h"
#include "dominion_helpers.h"
#include <stdarg.h>
#include <stdio.h>

int drawCard(int player, struct gameState *state)
{   int count;
    int deckCounter;
    if (state->deckCount[player] <= 0) { //Deck is empty

        //Step 1 Shuffle the discard pile back into a deck
        int i;
        //Move discard to deck
        for (i = 0; i < state->discardCount[player]; i++) {
            state->deck[player][i] = state->discard[player][i];
            state->discard[player][i] = -1;
        }

        state->deckCount[player] = state->discardCount[player];
        state->discardCount[player] = 0;//Reset discard

        //Shufffle the deck
        shuffle(player, state);//Shuffle the deck up and make it so that we can draw

        if (DEBUG) { //Debug statements
            printf("Deck count now: %d\n", state->deckCount[player]);
        }

        state->discardCount[player] = 0;

        //Step 2 Draw Card
        count = state->handCount[player];//Get current player's hand count

        if (DEBUG) { //Debug statements
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create a holder for the deck count

        if (deckCounter == 0)
            return -1;

        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    else {
        int count = state->handCount[player];//Get current hand count for player
        int deckCounter;
        if (DEBUG) { //Debug statements
            printf("Current hand count: %d\n", count);
        }

        deckCounter = state->deckCount[player];//Create holder for the deck count
        state->hand[player][count] = state->deck[player][deckCounter - 1];//Add card to the hand
        state->deckCount[player]--;
        state->handCount[player]++;//Increment hand count
    }

    return 0;
}

int updateCoins(int player, struct gameState *state, int bonus)
{
    int i;

    //reset coin count
    state->coins = 0;

    //add coins for each Treasure card in player's hand
    for (i = 0; i < state->handCount[player]; i++)
    {
        if (state->hand[player][i] == copper)
        {
            state->coins += 1;
        }
        else if (state->hand[player][i] == silver)
        {
            state->coins += 2;
        }
        else if (state->hand[player][i] == gold)
        {
            state->coins += 3;
        }
    }

    //add bonus
    state->coins += bonus;

    return 0;
}

int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{

    //if card is not trashed, added to Played pile
    if (trashFlag < 1)
    {
        //add card to played pile
        state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos];
        state->playedCardCount++;
    }

    //set played card to -1
    state->hand[currentPlayer][handPos] = -1;

    //remove card from player's hand
    if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
    {
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }
    else
    {
        //replace discarded card with last card in hand
        state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
        //set last card to -1
        state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
        //reduce number of cards in hand
        state->handCount[currentPlayer]--;
    }

    return 0;
}

int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
    //Note: supplyPos is enum of choosen card

    //check if supply pile is empty (0) or card is not used in game (-1)
    if ( supplyCount(supplyPos, state) < 1 )
    {
        return -1;
    }

    //added card for [whoseTurn] current player:
    // toFlag = 0 : add to discard
    // toFlag = 1 : add to deck
    // toFlag = 2 : add to hand

    if (toFlag == 1)
    {
        state->deck[ player ][ state->deckCount[player] ] = supplyPos;
        state->deckCount[player]++;
    }
    else if (toFlag == 2)
    {
        state->hand[ player ][ state->handCount[player] ] = supplyPos;
        state->handCount[player]++;
    }
    else
    {
        state->discard[player][ state->discardCount[player] ] = supplyPos;
        state->discardCount[player]++;
    }

    //decrease number in supply pile
    state->supplyCount[supplyPos]--;

    return 0;
}

int getCost(int cardNumber)
{
    switch( cardNumber )
    {
    case curse:
        return 0;
    case estate:
        return 2;
    case duchy:
        return 5;
    case province:
        return 8;
    case copper:
        return 0;
    case silver:
        return 3;
    case gold:
        return 6;
    case adventurer:
        return 6;
    case council_room:
        return 5;
    case feast:
        return 4;
    case gardens:
        return 4;
    case mine:
        return 5;
    case remodel:
        return 4;
    case smithy:
        return 4;
    case village:
        return 3;
    case baron:
        return 4;
    case great_hall:
        return 3;
    case minion:
        return 5;
    case steward:
        return 3;
    case tribute:
        return 5;
    case ambassador:
        return 3;
    case cutpurse:
        return 4;
    case embargo:
        return 2;
    case outpost:
        return 5;
    case salvager:
        return 4;
    case sea_hag:
        return 4;
    case treasure_map:
        return 4;
    }

    return -1;
}

int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)
{
    int i;
    int j;
    int k;
    int x;
    int index;
    int currentPlayer = whoseTurn(state);
    int nextPlayer = currentPlayer + 1;

    int temphand[MAX_HAND];// moved above the if statement
    int drawntreasure=0;
    int cardDrawn;
    int z = 0;// this is the counter for the temp hand
    if (nextPlayer > (state->numPlayers - 1)) {
        nextPlayer = 0;
    }


    //uses switch to select card and perform actions
    switch( card )
    {
    case adventurer:
        while(drawntreasure<2) {
            if (state->deckCount[currentPlayer] <1) { //if the deck is empty we need to shuffle discard and add to deck
                shuffle(currentPlayer, state);
            }
            drawCard(currentPlayer, state);
            cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer]-1];//top card of hand is most recently drawn card.
            if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
                drawntreasure++;
            else {
                temphand[z]=cardDrawn;
                state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
                z++;
            }
        }
        while(z-1>=0) {
            state->discard[currentPlayer][state->discardCount[currentPlayer]++]=temphand[z-1]; // discard all cards in play that have been drawn
            z=z-1;
        }
        return 0;

    case council_room:
        //+4 Cards
        for (i = 0; i < 4; i++)
        {
            drawCard(currentPlayer, state);
        }

        //+1 Buy
        state->numBuys++;

        //Each other player draws a card
        for (i = 0; i < state->numPlayers; i++)
        {
            if ( i != currentPlayer )
            {
                drawCard(i, state);
            }
        }

        //put played card in played card pile
        discardCard(handPos, currentPlayer, state, 0);

        return 0;

    case feast:
        //gain card with cost up to 5
        //Backup hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++) {
            temphand[i] = state->hand[currentPlayer][i];//Backup card
            state->hand[currentPlayer][i] = -1;//Set to nothing
        }
        //Backup hand

        //Update Coins for Buy
        updateCoins(currentPlayer, state, 5);
        x = 1;//Condition to loop on
        while( x == 1) {//Buy one card
            if (supplyCount(choice1, state) <= 0) {
                if (DEBUG)
                    printf("None of that card left, sorry!\n");

                if (DEBUG) {
                    printf("Cards Left: %d\n", supplyCount(choice1, state));
                }
            }
            else if (state->coins < getCost(choice1)) {
                printf("That card is too expensive!\n");

                if (DEBUG) {
                    printf("Coins: %d < %d\n", state->coins, getCost(choice1));
                }
            }
            else {

                if (DEBUG) {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

                gainCard(choice1, state, 0, currentPlayer);//Gain the card
                x = 0;//No more buying cards

                if (DEBUG) {
                    printf("Deck Count: %d\n", state->handCount[currentPlayer] + state->deckCount[currentPlayer] + state->discardCount[currentPlayer]);
                }

            }
        }

        //Reset Hand
        for (i = 0; i <= state->handCount[currentPlayer]; i++) {
            state->hand[currentPlayer][i] = temphand[i];
            temphand[i] = -1;
        }
        //Reset Hand

        return 0;

    case gardens:
        return -1;

    case mine:
        return mineCardEffect(state, currentPlayer, choice1, choice2, handPos);        

    case remodel:
        j = state->hand[currentPlayer][choice1];  //store card we will trash

        if ( (getCost(state->hand[currentPlayer][choice1]) + 2) > getCost(choice2) )
        {
            return -1;
        }

        gainCard(choice2, state, 0, currentPlayer);

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);

        //discard trashed card
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == j)
            {
                discardCard(i, currentPlayer, state, 0);
                break;
            }
        }


        return 0;

    case smithy:
        //+3 Cards
        for (i = 0; i < 3; i++)
        {
            drawCard(currentPlayer, state);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case village:
        //+1 Card
        drawCard(currentPlayer, state);

        //+2 Actions
        state->numActions = state->numActions + 2;

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case baron:
        return baronCardEffect(state, currentPlayer, choice1);

    case great_hall:
        //+1 Card
        drawCard(currentPlayer, state);

        //+1 Actions
        state->numActions++;

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case minion:
        return minionCardEffect(state, currentPlayer, choice1, choice2, handPos);

    case steward:
        if (choice1 == 1)
        {
            //+2 cards
            drawCard(currentPlayer, state);
            drawCard(currentPlayer, state);
        }
        else if (choice1 == 2)
        {
            //+2 coins
            state->coins = state->coins + 2;
        }
        else
        {
            //trash 2 cards in hand
            discardCard(choice2, currentPlayer, state, 1);
            discardCard(choice3, currentPlayer, state, 1);
        }

        //discard card from hand
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case tribute:
        return tributeCardEffect(state, currentPlayer, nextPlayer);

    case ambassador:
        return ambassadorCardEffect(state, currentPlayer, choice1, choice2, handPos);

    case cutpurse:

        updateCoins(currentPlayer, state, 2);
        for (i = 0; i < state->numPlayers; i++)
        {
            if (i != currentPlayer)
            {
                for (j = 0; j < state->handCount[i]; j++)
                {
                    if (state->hand[i][j] == copper)
                    {
                        discardCard(j, i, state, 0);
                        break;
                    }
                    if (j == state->handCount[i])
                    {
                        for (k = 0; k < state->handCount[i]; k++)
                        {
                            if (DEBUG)
                                printf("Player %d reveals card number %d\n", i, state->hand[i][k]);
                        }
                        break;
                    }
                }

            }

        }

        //discard played card from hand
        discardCard(handPos, currentPlayer, state, 0);

        return 0;


    case embargo:
        //+2 Coins
        state->coins = state->coins + 2;

        //see if selected pile is in play
        if ( state->supplyCount[choice1] == -1 )
        {
            return -1;
        }

        //add embargo token to selected supply pile
        state->embargoTokens[choice1]++;

        //trash card
        discardCard(handPos, currentPlayer, state, 1);
        return 0;

    case outpost:
        //set outpost flag
        state->outpostPlayed++;

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case salvager:
        //+1 buy
        state->numBuys++;

        if (choice1)
        {
            //gain coins equal to trashed card
            state->coins = state->coins + getCost( handCard(choice1, state) );
            //trash card
            discardCard(choice1, currentPlayer, state, 1);
        }

        //discard card
        discardCard(handPos, currentPlayer, state, 0);
        return 0;

    case sea_hag:
        for (i = 0; i < state->numPlayers; i++) {
            if (i != currentPlayer) {
                state->discard[i][state->discardCount[i]] = state->deck[i][state->deckCount[i]--];
                state->deckCount[i]--;
                state->discardCount[i]++;
                state->deck[i][state->deckCount[i]--] = curse;//Top card now a curse
            }
        }
        return 0;

    case treasure_map:
        //search hand for another treasure_map
        index = -1;
        for (i = 0; i < state->handCount[currentPlayer]; i++)
        {
            if (state->hand[currentPlayer][i] == treasure_map && i != handPos)
            {
                index = i;
                break;
            }
        }
        if (index > -1)
        {
            //trash both treasure cards
            discardCard(handPos, currentPlayer, state, 1);
            discardCard(index, currentPlayer, state, 1);

            //gain 4 Gold cards
            for (i = 0; i < 4; i++)
            {
                gainCard(gold, state, 1, currentPlayer);
            }

            //return success
            return 1;
        }

        //no second treasure_map found in hand
        return -1;
    }

    return -1;
}

void assert(int condition, const char* message, ...)
{
    if(DEBUG || !condition)
    {
        char messageBuf[250];
        va_list args;
        va_start(args, message);
        vsnprintf(messageBuf, sizeof(messageBuf), message, args);
        va_end(args);

        if(!condition)
        {
            printf("FAILED - %s", messageBuf);
        }
        else
        {
            printf("DEBUG - %s", messageBuf);
        }
        
    }
}