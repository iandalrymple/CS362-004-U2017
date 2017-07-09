// Desc: 			Unit test for shuffle function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/04/2017
// Function requirements:
//				1 cards in deck are reorganized 
// 				2 shuffle ONLY impacts the intended sinlge player
//				3 nothing else for player is changed
//				4 if player has no cards in deck return -1 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NUM_CARDS 27
#define HAND_COUNT 10

// Requirement 4 
void shuffleDeckEmptyTest()
{
	int j; 						// Simple indexer
	struct gameState G1; 		
		
	// Check to make sure it bombs out for no cards in deck (0)
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		G1.deckCount[j] = 0;
		if(shuffle(j, &G1) == -1)
			printf("PASSED init count check for player %d with count of %d.\n", j, 0);
		else
			printf("FAILED init count check for player %d.\n", j);
	}
	
	// Check to make sure it bombs out for no cards in deck (-1)
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		G1.deckCount[j] = -1;
		if(shuffle(j, &G1) == -1)
			printf("PASSED init count check for player %d with count of %d.\n", j, -1);
		else
			printf("FAILED init count check for player %d.\n", j);
	}
	
	printf("\n");
}

// Requirement 1, 2 and 3
void shuffleCountTest()
{
	int j, k, m, n, p; 					// Simple indexers
	struct gameState G1; 				// Before shuffle 
	struct gameState G2; 				// After shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	initializeGame((int)MAX_PLAYERS, kings, 23, &G1);
						
	// Assign each player 
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		// Assign the card values - just putting index into value for the sake 
		// of testing 
		for(k = 0; k < MAX_DECK; k++)
		{
			G2.deck[j][k] = G1.deck[j][k] = k;
		}
		
		// Set the deck count 
		G1.deckCount[j] = G2.deckCount[j] = (int)HAND_COUNT;

		// Make a copy of the game state 
		memcpy(&G2, &G1, sizeof(struct gameState));
		
		// Shuffle the deck 
		int result = shuffle(j, &G2);
		if(result < -1) 
			printf("FAILED: player has no cards in deck but was set to 10.\n");		
		
		// Get the counts of each card type in before and after shuffle decks 
		int G1Counts[(int)NUM_CARDS]; 
		int G2Counts[(int)NUM_CARDS];
		for(n = 0; n < (int)NUM_CARDS; n++)
			G1Counts[n] = G2Counts[n] = 0;
		for(m = 0; m < (int)HAND_COUNT; m++)
		{
			G1Counts[G1.deck[j][m]]++;
			G2Counts[G2.deck[j][m]]++;			
		}
		
		// Compare the counts - should be equal 
		int countFlag = 0;
		for(p = 0; p < (int)NUM_CARDS; p++)
		{
			if(G1Counts[p] != G2Counts[p])
			{
				printf("FAILED Player = %d CardValue = %d CardCountRaw = %d, CardCountShuffle = %d.\n", j, p, G1Counts[p], G2Counts[p]);
				countFlag++;
			}
		}
				
		// Check to make sure the cards are shuffled ISH. Meaning at least one index has different card in it.
		int mixCounter = 0;
		for(m = 0; m < (int)HAND_COUNT; m++)
		{
			if(G1.deck[j][m] != G2.deck[j][m])
			{
				mixCounter++;
			}
		}
		
		// Check to make sure nothing else is changed for this player and the other players
		int somethingChanged = 0;
		for(k = 0; k < MAX_DECK; k++)
			G1.deck[j][k] = G2.deck[j][k];
		result = gameStateCmp(&G1, &G2);
		if(result != 1000)
			somethingChanged = result;
			
		// Print out the final result 
		if(mixCounter > 0 && countFlag == 0 && somethingChanged == 0)
			printf("PASSED for player %d for bin count and randomness check and nothing else changed for this player or other players.\n", j);
		else 
			printf("FAILED for player %d with countFlag = %d and randomFlag = %d and somethingChanged %d.\n", j, countFlag, mixCounter, somethingChanged);				
	}	
	printf("\n");	
}

// Simple robustness test to make sure the program handles bad bounds elegantly 
void negativePlayerTest()
{
	int j, k, m; 				// Simple indexers
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 

	// Assign each player 
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		// Assign the card values 
		for(k = 0; k < MAX_DECK; k++)
		{
			G2.deck[j][k] = G1.deck[j][k] = k;
		}
		
		// Set the deck count 
		G1.deckCount[j] = G2.deckCount[j] = (int)HAND_COUNT;
		
		// Shuffle the deck 
		int result = shuffle(-1, &G2);
	
		// Nothing should be returned as an exception should be thrown or 
		// some negative flag maybe should be sent back 
		if(result > -1)
		{
			printf("FAILED: returned a value of %d which indicates the function completed but negative player index submitted.\n", result);
			for(m = 0; m < (int)HAND_COUNT; m++)
				printf("Result before %d result after %d\n", G1.deck[j][m], G2.deck[j][m]);
		}
		else 
			printf("PASSED: returned a value of %d which indicates the function bombed out and returned an impossible value.\n", result);
	}
}

int main () 
{
	printf("\nUNIT TEST 1\n");
	shuffleDeckEmptyTest();
	shuffleCountTest();
	negativePlayerTest();
	return 0;
}

