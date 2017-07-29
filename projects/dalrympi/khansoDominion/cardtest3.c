// Desc: 			Unit test for fVillage function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/08/2017
// Requirements:
// 1 - gain two actions 
// 2 - gain a card from deck 
// 3 - gain a card to hand
// 4 - do not mutate any other players or any other features of the active player
// 5 - get rid of the village card to discard pile 

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

// All requirements covered 
void actionAndDiscardTest()
{
	int i, j;
	int gsResult;
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
		
		// Copy over the state before calling FUT
		memcpy (&G2, &G1, sizeof(struct gameState));
		
		// Call fVillage
		if(fVillage(&G1, i, (int)VILLAGE_IDX))
			printf("FAILED: returned value greater than 0 which means something went wrong.\n");
		
		// Check the action count
		if(G1.numActions == (int)NUM_ACTIONS + 2)
			printf("PASSED: player %d action count tested correctly equal to %d.\n",i , (int)NUM_ACTIONS + 2);
		else 
			printf("FAILED: player %d action count incorrectly equal to %d.\n",i , G1.numActions);	
		
		// Check to make sure the village card is gone 
		if(G1.hand[i][(int)VILLAGE_IDX] == 5)
			printf("PASSED: player %d the village card is gone from hand as it should be and have a new card.\n", i);
		else 
			printf("FAILED: player %d the village card is still in hand.\n", i);	
		
		// Check to make sure discard pile has another card 
		if(G1.discardCount[i] == G2.discardCount[i] + 1)
			printf("PASSED: player %d the discardCount has been incremented.\n", i);
		else 
			printf("FAILED: player %d the discardCount is off.\n", i);	
		
		// Reset hand, discard and deck and played before checking for mutations 
		G1.handCount[i] = G2.handCount[i];
		G1.deckCount[i] = G2.deckCount[i];
		G1.discardCount[i] = G2.discardCount[i];
		G1.playedCardCount = G2.playedCardCount;
		G1.numActions = G2.numActions;
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = G2.hand[i][j];
			G1.deck[i][j] = G2.deck[i][j];
			G1.discard[i][j] = G2.discard[i][j];
			G1.playedCards[j] = G2.playedCards[j];
		}
		gsResult = gameStateCmp(&G1, &G2);
		if(gsResult != 1000)
			printf("FAILED: player %d mutate test with value %d.\n", i, gsResult);
		else
			printf("PASSED: player %d mutate count test.\n", i);	
	}
}

int main () 
{
	printf("\nCARD TEST 3 = VILLAGE\n");
	actionAndDiscardTest();
	return 0;
}