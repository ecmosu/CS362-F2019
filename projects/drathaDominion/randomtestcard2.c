#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "Minion"

int main() {

    srand(time(NULL));
	
	int k[10] = {adventurer, baron, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	
	int successfulTests = 0;
	int failedTests = 0;
	int numberOfTests = 0;

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


    while(numberOfTests != 30){
		int numPlayers = 2 + (rand() % 3);
		int thisPlayer = 0;
		int seed = 10 + (rand() % 1001);
		
		struct gameState *G = malloc(sizeof(struct gameState));

		initializeGame(numPlayers, k, seed, G);

		G->handCount[thisPlayer] = 1 + (rand() % 200);
		for(int i=0; i<G->handCount[thisPlayer]; i++){
			G->hand[thisPlayer][i] = rand() % 28;
		}
		G->handCount[thisPlayer+1] = rand() % 200;
		
		G->deckCount[thisPlayer] = rand() % 200;
		G->discardCount[thisPlayer] = rand() % 200;
		G->deckCount[thisPlayer+1] = rand() % 200;
		G->discardCount[thisPlayer+1] = rand() % 200;
		G->coins = 0;
		int origDiscardCntCPlayer = G->discardCount[thisPlayer];
		int origHandCntCPlayer = G->handCount[thisPlayer];
		int origCoin = G->coins;
		//int origDiscardCntNextPlayer = G->discardCount[thisPlayer+1];
		//int origHandCntNextPlayer = G->handCount[thisPlayer+1];
		
		int handpos;
		if(G->handCount[thisPlayer] == 0){
			handpos = 0;
		} else {
			handpos = rand() % G->handCount[thisPlayer];
		}
		int choice1 = rand() % 2; 
		int choice2 = rand() % 2;
		int choice3 = rand() % 2;
		int bonus = rand() % 2;

		cardEffect(minion, choice1, choice2, choice3, G, handpos, &bonus);

		if(choice1 == 1 && G->discardCount[thisPlayer] == origDiscardCntCPlayer+origHandCntCPlayer && G->coins == origCoin+2){
			successfulTests++;
		}
		else if(choice1 == 0 && choice2 == 1 && G->discardCount[thisPlayer] == origDiscardCntCPlayer+origHandCntCPlayer && G->handCount[thisPlayer] == 4){
			successfulTests++;
		}
		else {
			failedTests++;
		}

		numberOfTests++;
		free(G);
    }


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n", TESTCARD);
	printf("Successful Tests = %d, Failed Tests = %d.\n\n", successfulTests, failedTests);
	
	return 0;
}
