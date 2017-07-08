// Desc: 			Unit test for fadventurer function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/08/2017

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
#define VILLAGE_IDX		2
#define TEST_DECK 		5
#define TEST_DISCARD 	5
#define NUM_ACTIONS		3
#define PLAYED_COUNT 	45

void actionAndDiscardTest()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = 5;
			G1.deck[i][j] = 5;
			G1.discard[i][j] = 5;
			G1.playedCards[j] = 5;
		}
		
		// Insert the adventurer
		G1.hand[i][(int)VILLAGE_IDX] = village;
		
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		G1.playedCardCount = (int)PLAYED_COUNT; 
		
		// Set up the number of actions 
		G1.numActions = (int)NUM_ACTIONS;
		
		// Call fVillage
		if(fVillage(&G1, i, (int)VILLAGE_IDX))
			printf("FAILED: returned value greater than 0 which means something went wrong.\n");
		
		// Check the action count
		if(G1.numActions == (int)NUM_ACTIONS + 2)
			printf("PASSED: player %d action count tested correctly equal to %d.\n",i , (int)NUM_ACTIONS + 2);
		else 
			printf("FAILED: player %d action count incorrectly equal to %d.\n",i , G1.numActions);	
		
		// Check to make sure the village card is gone 
		// for(j = 0; j < G1.handCount[i]; j++)
			// printf("%d\n", G1.hand[i][j]); 
		if(G1.hand[i][(int)VILLAGE_IDX] == 5)
			printf("PASSED: player %d the village card is gone from hand as it should be.\n", i);
		else 
			printf("FAILED: player %d the village card is still in hand.\n", i);	
	}
}

int main () 
{
	printf("\nCARD TEST 3 = VILLAGE\n");
	actionAndDiscardTest();
	return 0;
}