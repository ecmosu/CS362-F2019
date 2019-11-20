#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TESTCARD "Baron"

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
		int estateCheck = -1;
		
		struct gameState *G = malloc(sizeof(struct gameState));

		initializeGame(numPlayers, k, seed, G);

		G->handCount[thisPlayer] = rand() % 10;
		for(int i=0; i<G->handCount[thisPlayer]; i++){
			G->hand[thisPlayer][i] = rand() % 28;
		}
		G->deckCount[thisPlayer] = rand() % MAX_DECK;
		G->discardCount[thisPlayer] = rand() % MAX_DECK;
		G->numActions = 0;
		G->coins = 0;
		int originalDiscardCount = G->discardCount[thisPlayer];
		int originalNumActions = G->numActions;
		
		int handpos;
		if(G->handCount[thisPlayer] == 0){
			handpos = 0;
		} else {
			handpos = rand() % G->handCount[thisPlayer];
		}
		int choice1 = rand() % 6; 
		int choice2 = rand() % 6;
		int choice3 = rand() % 6;
		int bonus = rand() % 6;

		cardEffect(baron, choice1, choice2, choice3, G, handpos, &bonus);

		if(choice1 == 0 && G->discardCount[thisPlayer] == originalDiscardCount+1 && G->numActions == originalNumActions+1){
			successfulTests++;
		}
		else if(choice1 > 0 && estateCheck == -1 && G->discardCount[thisPlayer] == originalDiscardCount+1 && G->numActions == originalNumActions+1){
			successfulTests++;
		}
		else if(choice1 > 0 && estateCheck && G->coins == 4 && G->numActions == originalNumActions+1){
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
