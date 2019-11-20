#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "Tribute"

int cardType(int cardValue)
{
    if (cardValue >= 4 && cardValue <= 6)
    {
        return 1;
    }
    else if (cardValue >= 7 && cardValue != 10 && cardValue != 16)
    {
        return 2;
    }
    else
    {
        if (cardValue != 0)
        {
            return 3;
        }
        else
        {
            return 0;
        }
    }
}

int main()
{

    srand(time(NULL));

    int k[10] = {adventurer, baron, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy, council_room};

    int successfulTests = 0;
    int failedTests = 0;
    int numberOfTests = 0;

    printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    while (numberOfTests != 30)
    {
        int numPlayers = 2 + (rand() % 3);
        int thisPlayer = 0;
        int nextPlayer = 1;
        int seed = 10 + (rand() % 1001);

        struct gameState *G = malloc(sizeof(struct gameState));

        initializeGame(numPlayers, k, seed, G);

        //Initialize handCount for this player and nextplayer
        G->handCount[thisPlayer] = 1 + (rand() % 10);
        for (int i = 0; i < G->handCount[thisPlayer]; i++)
        {
            G->hand[thisPlayer][i] = rand() % 28;
        }
        G->handCount[nextPlayer] = rand() % 10;
        for (int i = 0; i < G->handCount[nextPlayer]; i++)
        {
            G->hand[nextPlayer][i] = rand() % 28;
        }

        //Initialize deckCount for this player and nextplayer
        G->deckCount[thisPlayer] = rand() % 10;
        for (int i = 0; i < G->deckCount[thisPlayer]; i++)
        {
            G->deck[thisPlayer][i] = rand() % 28;
        }
        G->deckCount[nextPlayer] = rand() % 10;
        for (int i = 0; i < G->deckCount[nextPlayer]; i++)
        {
            G->deck[thisPlayer][i] = rand() % 28;
        }

        //Initialize discardCount for this player and nextplayer
        G->discardCount[thisPlayer] = rand() % 10;
        for (int i = 0; i < G->discardCount[thisPlayer]; i++)
        {
            G->discard[thisPlayer][i] = rand() % 28;
        }
        G->discardCount[nextPlayer] = rand() % 10;
        for (int i = 0; i < G->discardCount[nextPlayer]; i++)
        {
            G->discard[nextPlayer][i] = rand() % 28;
        }

        G->coins = 0;
        G->numActions = 0;

        //Initialize original values before the game starts
        //int origDiscardCntCPlayer = G->discardCount[thisPlayer];
        //int origDeckCntCPlayer = G->deckCount[thisPlayer];
        int origHandCntCPlayer = G->handCount[thisPlayer];
        int origDiscardCntNextPlayer = G->discardCount[nextPlayer];
        int origDeckCntNextPlayer = G->deckCount[nextPlayer];
        //int origHandCntNextPlayer = G->handCount[nextPlayer];
        int origCoin = G->coins;
        int origNumActions = G->numActions;
        int origDiscardCard1;
        int origDiscardCard2;
        int origDeckCard1;
        int origDeckCard2;

        //Initialize discard cards if used
        if (G->discardCount[nextPlayer] > 1)
        {
            origDiscardCard1 = cardType(G->discard[nextPlayer][0]);
            origDiscardCard2 = cardType(G->discard[nextPlayer][1]);
        }
        else if (G->discardCount[nextPlayer] == 1)
        {
            origDiscardCard1 = cardType(G->discard[nextPlayer][0]);
        }
        else
        {
            origDiscardCard1 = -1;
        }

        //Initialize deck cards if used
        if (G->deckCount[nextPlayer] > 1)
        {
            origDeckCard1 = cardType(G->deck[nextPlayer][0]);
            origDeckCard2 = cardType(G->deck[nextPlayer][1]);
        }
        else if (G->deckCount[nextPlayer] == 1)
        {
            origDeckCard1 = cardType(G->deck[nextPlayer][0]);
        }
        else
        {
            origDeckCard1 = -1;
        }

        int handpos;
        if (G->handCount[thisPlayer] == 0)
        {
            handpos = 0;
        }
        else
        {
            handpos = rand() % G->handCount[thisPlayer];
        }
        int choice1 = rand() % 2;
        int choice2 = rand() % 2;
        int choice3 = rand() % 2;
        int bonus = rand() % 2;

        cardEffect(tribute, choice1, choice2, choice3, G, handpos, &bonus);

        if (origDeckCntNextPlayer == 0)
        {
            if (origDiscardCntNextPlayer == 0)
            {
                if (origNumActions == G->numActions && origCoin == G->coins && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else
                {
                    failedTests++;
                }
            }
            else if (origDiscardCntNextPlayer == 1)
            {
                if (origDiscardCard1 == 1 && G->coins == origCoin + 2 && origNumActions == G->numActions && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else
                {
                    if (origDiscardCard1 != 0 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
                    {
                        successfulTests++;
                    }
                    else
                    {
                        failedTests++;
                    }
                }
            }
            else
            {
                if (origDiscardCard1 == 1 && origDiscardCard2 == 1 && G->coins == origCoin + 4 && origNumActions == G->numActions && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 1 && origDiscardCard2 == 2 && G->coins == origCoin + 2 && origNumActions == G->numActions && origHandCntCPlayer + 2 == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 1 && origDiscardCard2 == 3 && G->coins == origCoin + 2 && origNumActions == G->numActions + 2 && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDiscardCard2 == 1 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin + 2 == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDiscardCard2 == 2 && origHandCntCPlayer + 4 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDiscardCard2 == 3 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDiscardCard2 == 1 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin + 2 == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDiscardCard2 == 2 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDiscardCard2 == 3 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 4 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else
                {
                    failedTests++;
                }
            }
        }
        else if (origDeckCntNextPlayer == 1)
        {
            if (origDiscardCntNextPlayer == 0)
            {
                if (origNumActions == G->numActions && origCoin == G->coins && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else
                {
                    failedTests++;
                }
            }
            else
            {
                if (origDiscardCard1 == 1 && origDeckCard1 == 1 && G->coins == origCoin + 4 && origNumActions == G->numActions && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 1 && origDeckCard1 == 2 && G->coins == origCoin + 2 && origNumActions == G->numActions && origHandCntCPlayer + 2 == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 1 && origDeckCard1 == 3 && G->coins == origCoin + 2 && origNumActions == G->numActions + 2 && origHandCntCPlayer == G->handCount[thisPlayer])
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDeckCard1 == 1 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin + 2 == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDeckCard1 == 2 && origHandCntCPlayer + 4 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 2 && origDeckCard1 == 3 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDeckCard1 == 1 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin + 2 == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDeckCard1 == 2 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else if (origDiscardCard1 == 3 && origDeckCard1 == 3 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 4 == G->numActions && origCoin == G->coins)
                {
                    successfulTests++;
                }
                else
                {
                    failedTests++;
                }
            }
        }
        else
        {
            if (origDeckCard2 == 1 && origDeckCard1 == 1 && G->coins == origCoin + 4 && origNumActions == G->numActions && origHandCntCPlayer == G->handCount[thisPlayer])
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 1 && origDeckCard1 == 2 && G->coins == origCoin + 2 && origNumActions == G->numActions && origHandCntCPlayer + 2 == G->handCount[thisPlayer])
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 1 && origDeckCard1 == 3 && G->coins == origCoin + 2 && origNumActions == G->numActions + 2 && origHandCntCPlayer == G->handCount[thisPlayer])
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 2 && origDeckCard1 == 1 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin + 2 == G->coins)
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 2 && origDeckCard1 == 2 && origHandCntCPlayer + 4 == G->handCount[thisPlayer] && origNumActions == G->numActions && origCoin == G->coins)
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 2 && origDeckCard1 == 3 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 3 && origDeckCard1 == 1 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin + 2 == G->coins)
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 3 && origDeckCard1 == 2 && origHandCntCPlayer + 2 == G->handCount[thisPlayer] && origNumActions + 2 == G->numActions && origCoin == G->coins)
            {
                successfulTests++;
            }
            else if (origDeckCard2 == 3 && origDeckCard1 == 3 && origHandCntCPlayer == G->handCount[thisPlayer] && origNumActions + 4 == G->numActions && origCoin == G->coins)
            {
                successfulTests++;
            }
            else
            {
                failedTests++;
            }
        }

        numberOfTests++;
        free(G);
    }

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);
    printf("Successful Tests = %d, Failed Tests = %d.\n\n", successfulTests, failedTests);

    return 0;
}
