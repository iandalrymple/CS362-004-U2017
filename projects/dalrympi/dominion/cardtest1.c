// Desc: 			Unit test for fSmithy function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/07/2017

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NUM_CARDS 		27
#define TEST_HAND 		5
#define SMITHY_IDX		2
#define TEST_DECK 		100
#define TEST_DISCARD 	100

void smithyTest()
{
	struct gameState G1; // Working 
	struct gameState G2; // Snapshot 
	int i, j, k;
	int smithyResult[MAX_PLAYERS] = {1, 1, 1, 1};
	int countResult[MAX_PLAYERS] = {1, 1, 1, 1};
		
	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G2.hand[i][j] = j;
			G2.deck[i][j] = j;
			G2.discard[i][j] = j;
		}
		
		// Insert the smithy 
		G2.hand[i][(int)SMITHY_IDX] = smithy;
		
		// Set up counts 
		G2.handCount[i] = (int)TEST_HAND;
		G2.deckCount[i] = (int)TEST_DECK;
		G2.discardCount[i] = (int)TEST_DISCARD;
		
		// Copy over the state before calling smithy 
		memcpy (&G1, &G2, sizeof(struct gameState));
		
		// Call fSmithy
		if(fSmithy(&G2, i, (int)SMITHY_IDX))
			printf("Should not be here\n");
		
		// Now compare the hands before and after 
		for(k = 0; k < (int)TEST_HAND; k++)
		{
			if((G1.hand[i][k] != G2.hand[i][k]) && (k != (int)SMITHY_IDX))
				smithyResult[i] = 0;
		}
		
		// Check the hand count 
		if(G2.handCount[i] != ((int)TEST_HAND + 2))
			countResult[i] = 0;	
		
		// int y = 0;
		// for(y = 0; y < 10; y++)
			// printf("%d %d\n", G1.hand[i][y], G2.hand[i][y]);
	}
	
	// Present the results 
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		if(smithyResult[i] == 0)
			printf("FAILED player %d for smithy removal.\n", i);
		else
			printf("PASSED player %d for smithy removal.\n", i);
		if(countResult[i] == 0)
			printf("FAILED player %d for hand count.\n", i);
		else
			printf("PASSED player %d for hand count.\n", i);
	}	
}
		
int main () 
{
	printf("\nCARD TEST 1 = SMITHY\n");
	smithyTest();
	return 0;
}