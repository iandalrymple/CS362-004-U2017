// Desc: 			Unit test for fadventurer function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/08/2017
// Requirements
// 1 - treasure in hand increased by 2 
// 2 - adventurer is kept in hand 
// 3 - cards drawn that are not treasure sent to discard pile 
// 4 - other players not mutated 
// 5 - other attributes beyond deck, hand, discard played are not mutated 

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
#define ADV_IDX			2
#define TEST_DECK 		5
#define TEST_DISCARD 	5

// Requirement 1, 2, 3, 4, and 5 
void treasureCount()
{
	int gsResult;
	int i, j;
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
		}
		
		// Insert the adventurer
		G1.hand[i][(int)ADV_IDX] = adventurer;
		
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Copy over the state before calling FUT
		memcpy (&G2, &G1, sizeof(struct gameState));
		
		// Call fadventurer
		if(adventurerEffect(i, (int)ADV_IDX, &G1))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] == 7)
			printf("PASSED: player %d handcount tested correctly equal to 7.\n", i);
		else 
			printf("FAILED: player %d handcount incorrectly equal to %d.\n", i, G1.handCount[i]);	
		
		// Check the discard pile count 
		if(G1.discardCount[i] == (G2.discardCount[i] + ((G1.deckCount[i] - G2.deckCount[i]) - (G2.handCount[i] - G1.handCount[i]))))
			printf("PASSED: player %d discard count test.\n", i);
		else
			printf("FAILED: player %d discard count test.\n", i);
		
		// Reset hand, discard and deck and played before checking for mutations 
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
			printf("FAILED: player %d mutate test.\n", i);
		else
			printf("PASSED: player %d mutate count test.\n", i);
	}
}

// Basic check to make sure you have adventurer in hand before allowing the actions to happen
void noAdvTest()
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
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Call fadventurer
		if(adventurerEffect(i, (int)ADV_IDX, &G1))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] != (int)TEST_HAND)
			printf("FAILED: player %d did not havea an adventurer and still performed function and card adds.\n", i);
		else 
			printf("PASSED: player %d no adventurer so nothing happened correctly.\n", i);	
	}
}

// Basic check to make sure goofy values cannot be passed into the player index 
void currentPlayerTest()
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
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Call fadventurer
		if(adventurerEffect(i, 6, &G1))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] != (int)TEST_HAND)
			printf("FAILED: player %d bad player passed in and still performed function.\n", i);
		else 
			printf("PASSED: player %d bad player and function did not execute which is correct.\n", i);	
	}
}
	
int main () 
{
	printf("\nCARD TEST 2 = ADVENTURER\n");
	treasureCount();
	noAdvTest();
	currentPlayerTest();
	return 0;
}