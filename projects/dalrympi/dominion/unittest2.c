// Desc: 			Unit test for fullDeckCount function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/04/2017

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define DECK_SIZE 		10
#define HAND_SIZE 		25
#define DISCARD_SIZE 	15
#define FILLER_CARD  	2
#define SEED_CARD 		22
#define SEED_COUNT 		4
	
void deckCountTest()
{
	int j, k; 						// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	printf("Start of deck count check test.\n");
	
	// Assign each player 
	for(j = 0; j < (int)MAX_PLAYERS; j++)
	{		
		// Assign the card values 
		for(k = 0; k < (int)MAX_DECK; k++)
		{
			G1.deck[j][k] = (int)FILLER_CARD;
		}
		
		// Set the counts of each pile 
		G1.handCount[j] = 0;
		G1.discardCount[j] = 0;
		G1.deckCount[j] = (int)DECK_SIZE;

		// Plant some seeds for the card we want to count 
		G1.deck[j][0] = (int)SEED_CARD;
		G1.deck[j][(int)DECK_SIZE - 1] = (int)SEED_CARD;
		G1.deck[j][3] = (int)SEED_CARD;
		G1.deck[j][7] = (int)SEED_CARD;
			
		// Compare the counts - should be equal 
		int failFlag = 0;
		if(fullDeckCount(j, (int)SEED_CARD, &G1) != (int)SEED_COUNT)
		{
			failFlag++;
			globalFlag++;
		}

		// Report per player results 
		if(failFlag > 0)
			printf("FAILED deckCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
		else
			printf("PASSED deckCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
	}
	
	// Overall check 
	if(globalFlag > 0)
		printf("FAILED deck count check test.\n\n");
	else
		printf("PASSED deck count check test.\n\n");
}

void handCountTest()
{
	int j, k; 						// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	printf("Start of hand count check test.\n");
	
	// Assign each player 
	for(j = 0; j < (int)MAX_PLAYERS; j++)
	{		
		// Assign the card values 
		for(k = 0; k < (int)MAX_HAND; k++)
		{
			G1.hand[j][k] = (int)FILLER_CARD;
		}
		
		// Set the counts of each pile 
		G1.handCount[j] = (int)HAND_SIZE;
		G1.discardCount[j] = 0;
		G1.deckCount[j] = 0;

		// Plant some seeds for the card we want to count 
		G1.hand[j][0] = (int)SEED_CARD;
		G1.hand[j][(int)HAND_SIZE - 1] = (int)SEED_CARD;
		G1.hand[j][10] = (int)SEED_CARD;
		G1.hand[j][17] = (int)SEED_CARD;
			
		// Compare the counts - should be equal 
		int failFlag = 0;
		if(fullDeckCount(j, (int)SEED_CARD, &G1) != (int)SEED_COUNT)
		{
			failFlag++;
			globalFlag++;
		}

		// Report per player results 
		if(failFlag > 0)
			printf("FAILED handCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
		else
			printf("PASSED handCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
	}
	
	// Overall check 
	if(globalFlag > 0)
		printf("FAILED hand count check test.\n\n");
	else
		printf("PASSED hand count check test.\n\n");
}

void discardCountTest()
{
	int j, k; 					// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	printf("Start of discard count check test.\n");
	
	// Assign each player 
	for(j = 0; j < (int)MAX_PLAYERS; j++)
	{		
		// Assign the card values 
		for(k = 0; k < (int)MAX_DECK; k++)
		{
			G1.discard[j][k] = (int)FILLER_CARD;
		}
		
		// Set the counts of each pile 
		G1.handCount[j] = 0;
		G1.discardCount[j] = (int)DISCARD_SIZE;
		G1.deckCount[j] = 0;

		// Plant some seeds for the card we want to count 
		G1.discard[j][0] = (int)SEED_CARD;
		G1.discard[j][(int)DISCARD_SIZE - 1] = (int)SEED_CARD;
		G1.discard[j][5] = (int)SEED_CARD;
		G1.discard[j][6] = (int)SEED_CARD;
			
		// Compare the counts - should be equal 
		int failFlag = 0;
		if(fullDeckCount(j, (int)SEED_CARD, &G1) != (int)SEED_COUNT)
		{
			failFlag++;
			globalFlag++;
		}

		// Report per player results 
		if(failFlag > 0)
			printf("FAILED discardCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
		else
			printf("PASSED discardCountTestCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT);
	}
	
	// Overall check 
	if(globalFlag > 0)
		printf("FAILED discard count check test.\n\n");
	else
		printf("PASSED discard count check test.\n\n");
}

void allCountTest()
{
	int j, k; 					// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	printf("Start of ALL count check test.\n");
	
	// Assign each player 
	for(j = 0; j < (int)MAX_PLAYERS; j++)
	{		
		// Assign the card values 
		for(k = 0; k < (int)MAX_DECK; k++)
		{
			G1.deck[j][k] = (int)FILLER_CARD;
			G1.discard[j][k] = (int)FILLER_CARD;
		}
		for(k = 0; k < (int)MAX_HAND; k++)
		{
			G1.hand[j][k] = (int)FILLER_CARD;
		}
				
		// Set the counts of each pile 
		G1.handCount[j] = (int)HAND_SIZE;
		G1.discardCount[j] = (int)DISCARD_SIZE;
		G1.deckCount[j] = (int)DECK_SIZE;

		// Plant some seeds for the card we want to count 
		G1.hand[j][0] = (int)SEED_CARD;
		G1.hand[j][(int)HAND_SIZE - 1] = (int)SEED_CARD;
		G1.hand[j][11] = (int)SEED_CARD;
		G1.hand[j][16] = (int)SEED_CARD;
		
		// Plant some seeds for the card we want to count 
		G1.deck[j][0] = (int)SEED_CARD;
		G1.deck[j][(int)DECK_SIZE - 1] = (int)SEED_CARD;
		G1.deck[j][4] = (int)SEED_CARD;
		G1.deck[j][7] = (int)SEED_CARD;
		
		// Plant some seeds for the card we want to count 
		G1.discard[j][0] = (int)SEED_CARD;
		G1.discard[j][(int)DISCARD_SIZE - 1] = (int)SEED_CARD;
		G1.discard[j][3] = (int)SEED_CARD;
		G1.discard[j][8] = (int)SEED_CARD;
			
		// Compare the counts - should be equal 
		int failFlag = 0;
		if(fullDeckCount(j, (int)SEED_CARD, &G1) != (int)SEED_COUNT * 3)
		{
			failFlag++;
			globalFlag++;
		}

		// Report per player results 
		if(failFlag > 0)
			printf("FAILED allCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT * 3);
		else
			printf("PASSED allCountTestCountTest for player = %d with fullDeckCount = %d and should be %d.\n", j, fullDeckCount(j, (int)SEED_CARD, &G1), (int)SEED_COUNT * 3);
	}
	
	// Overall check 
	if(globalFlag > 0)
		printf("FAILED overall count check test.\n\n");
	else
		printf("PASSED overall count check test.\n\n");
}

int main() 
{
	printf("\nUNIT TEST 2.\n");
	deckCountTest();
	handCountTest();
	discardCountTest();
	allCountTest();
	return 0;
}

