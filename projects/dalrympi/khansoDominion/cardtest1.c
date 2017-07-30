// Desc: 			Unit test for smithyEffect function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/29/2017
// Requirements:
// 1. Current player should receive exact 3 cards and discard the smithy 
// 2. 3 cards should come from his own pile.
// 3. No state change should occur for other players.
// 4. No state change should occur to the victory card piles and kingdom card piles.

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

// Requirements 1 - 4
void smithyTest()
{
	int i, j, k;
	int gsResult;
	int smithyResult[MAX_PLAYERS] = {1, 1, 1, 1};
	int countResult[MAX_PLAYERS] = {1, 1, 1, 1};
	int deckResult[MAX_PLAYERS] = {1, 1, 1, 1};
	int stateResult[MAX_PLAYERS] = {1, 1, 1, 1};
	struct gameState G1; 				// Before shuffle 
	struct gameState G2; 				// After shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	initializeGame((int)MAX_PLAYERS, kings, 85, &G1);
			
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
		
		// Call smithyEffect
		if(smithyEffect(i, (int)SMITHY_IDX, &G2))
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
		
		// Check the deck count 
		if(G2.deckCount[i] != ((int)TEST_DECK - 2))
			deckResult[i] = 0;	
		
		// Check the state before and after and for all players 
		G2.handCount[i] = G1.handCount[i];
		G2.deckCount[i] = G1.deckCount[i];
		G2.discardCount[i] = G1.discardCount[i];
		G2.playedCardCount = G1.playedCardCount;
		for(j = 0; j < MAX_DECK; j++)
		{
			G2.hand[i][j] = G1.hand[i][j];
			G2.deck[i][j] = G1.deck[i][j];
			G2.discard[i][j] = G1.discard[i][j];
			G2.playedCards[j] = G1.playedCards[j];
		}
		gsResult = gameStateCmp(&G1, &G2);
		if(gsResult != 1000)
			stateResult[i] = 0;
		
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
		if(deckResult[i] == 0)
			printf("FAILED player %d for deck count.\n", i);
		else
			printf("PASSED player %d for deck count.\n", i);
		if(stateResult[i] == 0)
			printf("FAILED player %d for state mutated with value %d.\n", i, gsResult);
		else
			printf("PASSED player %d for state mutated.\n", i);
	}	
}
		
int main () 
{
	printf("\nCARD TEST 1 = SMITHY\n");
	smithyTest();
	return 0;
}