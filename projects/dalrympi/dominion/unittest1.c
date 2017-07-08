// Desc: 			Unit test for shuffle function in dominion.c
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

#define NUM_CARDS 27

void shuffleDeckEmptyTest()
{
	int j; 						// Simple indexer
	struct gameState G1; 		
	
	// Introduction
	printf("Testing empty deck.\n");
	
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

void shuffleCountTest()
{
	int j, k, m, n, p; 		// Simple indexers
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
		G1.deckCount[j] = G2.deckCount[j] = 10;

		// Shuffle the deck 
		int result = shuffle(j, &G2);
		if(result < -1) 
			printf("PLAYER HAS NO CARDS LEFT IN DECK - SHOULD NOT HAPPEN.\n");		
		
		// Get the counts of each card type in before and after shuffle decks 
		int G1Counts[27]; 
		int G2Counts[27];
		for(n = 0; n < 27; n++)
			G1Counts[n] = G2Counts[n] = 0;
		for(m = 0; m < 10; m++)
		{
			G1Counts[G1.deck[j][m]]++;
			G2Counts[G2.deck[j][m]]++;			
			//printf("Deck size = %d Player = %d CardIdx = %d Before = %d and after = %d\n", deckCount, j, m, G1.deck[j][m], G2.deck[j][m]);
		}
		
		// Compare the counts - should be equal 
		int countFlag = 0;
		for(p = 0; p < 27; p++)
		{
			if(G1Counts[p] != G2Counts[p])
			{
				printf("FAILED Player = %d CardValue = %d CardCountRaw = %d, CardCountShuffle = %d.\n", j, p, G1Counts[p], G2Counts[p]);
				countFlag++;
			}
		}
				
		// Check to make sure the cards are shuffled ISH
		int mixCounter = 0;
		for(m = 0; m < 10; m++)
		{
			if(G1.deck[j][m] != G2.deck[j][m])
			{
				mixCounter++;
			}
		}
		
		// Print out the final result 
		if(mixCounter > 0 && countFlag == 0)
			printf("PASSED for player %d for bin count and randomness check.\n", j);
		else 
			printf("FAILED for player %d with countFlag = %d and randomFlag = %d.\n", j, countFlag, mixCounter);				
	}	
	printf("\n");	
}

void negativePlayerTest()
{
	int j, k, m; 		// Simple indexers
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
		G1.deckCount[j] = G2.deckCount[j] = 10;
		
		// Shuffle the deck 
		int result = shuffle(-1, &G2);
		printf("result %d\n", result);
		for(m = 0; m < 10; m++)
			printf("%d %d\n", G1.deck[j][m], G2.deck[j][m]);
	}
}

int main () 
{
	printf("UNIT TEST 1\n");
	shuffleDeckEmptyTest();
	shuffleCountTest();
	negativePlayerTest();
	return 0;
}

