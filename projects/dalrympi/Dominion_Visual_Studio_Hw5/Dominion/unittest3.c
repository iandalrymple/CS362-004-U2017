// Desc: 			Unit test for isGameOver function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/04/2017
// Requirements:
// 1 - if no province in the supply then game over
// 2 - if three supply cards are empty then game over 
// 3 - no mutations in the gamestate 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define		NUM_CARDS		27
#define 	NUM_REPS		50
#define 	RAND_MULT 		5

// Requirement 1 and 3
void provinceTest()
{
	int j;
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	initializeGame((int)MAX_PLAYERS, kings, 23, &G1);
		
	// Make supply with no province 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 23;
		if(j == province)
			G1.supplyCount[j] = 0;
	}	
	
	// Make a copy of the game state 
	memcpy(&G2, &G1, sizeof(struct gameState));	
	
	// Check for results by calling FUT 
	if(isGameOver(&G1) == 1)
		printf("PASSED province test with correct return equal to 1.\n");
	else
		printf("FAILED province test with incorrect return equal to 0.\n");

	// Test with province 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 14;
		if(j == province)
			G1.supplyCount[j] = 2;
	}		
	
	// Make a copy of the game state 
	memcpy(&G2, &G1, sizeof(struct gameState));	
	
	// Check for results by calling FUT 
	if(isGameOver(&G1) == 0)
		printf("PASSED province test with correct return equal to 0.\n");
	else
		printf("FAILED province test with incorrect return equal to 1.\n");
	
	// Check to make sure nothing else is changed for this player and the other players
	int somethingChanged = gameStateCmp(&G1, &G2);
	if(somethingChanged != 1000)
		printf("FAILED province test as the FUT mutated the gameState.\n");
	else
		printf("PASSED province test as the FUT DID NOT mutate the gameState.\n");
	
	printf("\n");
}

// Requirement 2 and 3
void countTest()
{
	int j; 					// Simple indexers
	int zeroCounter; 			// Count the number of zero in supply for compare to FUT
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	initializeGame((int)MAX_PLAYERS, kings, 23, &G1);
					
	// Populate the supply counts randomly but dont allow zero for province
	zeroCounter = 0;
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 22;
		if(j == province)
			G1.supplyCount[j] = 23;
		if(j == 24 || j == 25 || j == 26)
			G1.supplyCount[j] = 0;
	}	
	
	// Now check for zeroes 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		if(G1.supplyCount[j] == 0) 
			zeroCounter++;
	}
			
	// Set zeroCounter for compare to isGameOver
	int zeroCounterPost = 0;
	if(zeroCounter >= 3)
		zeroCounterPost = 1;
	else 
		zeroCounterPost = 0;
	
	// Make a copy of the game state 
	memcpy(&G2, &G1, sizeof(struct gameState));
	
	// Pass into the FUT
	if(isGameOver(&G1) == zeroCounterPost)
		printf("PASSED countTest with zeroCounter %d and isGameOver %d \n", zeroCounter, isGameOver(&G1));
	else 
	{
		printf("FAILED countTest with zeroCounter %d and isGameOver %d\n", zeroCounter, isGameOver(&G1));
		for(j = 0; j < (int)NUM_CARDS; j++)
			printf("Card %d count %d\n", j, G1.supplyCount[j]);
	}
	
	// Check to make sure nothing else is changed for this player and the other players
	int somethingChanged = gameStateCmp(&G1, &G2);
	if(somethingChanged != 1000)
		printf("FAILED count test as the FUT mutated the gameState.\n");
	else
		printf("PASSED count test as the FUT DID NOT mutate the gameState.\n");
}

int main () 
{
	printf("\nUNIT TEST 3\n");	
	provinceTest();
	countTest();
	getchar();
	return 0;
}

