// Desc: 			Unit test for updateCoins function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/06/2017

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define		NUM_CARDS		27
#define 	NUM_REPS		10
#define 	RAND_MULT 		5

void updateCoinTest()
{
	int i, j, k, m, n; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFail = 0;
	
	// Get random stream and seed with time based 
	SelectStream(38);
	PutSeed(-1);
		
	// Iterate x number of times 
	for(i = 0; i < NUM_REPS; i++)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.hand[j][k] = floor(Random() * (int)NUM_CARDS);
			}
			
			// Set the hand count 
			G1.handCount[j] = floor(Random() * (int)NUM_CARDS);
			
			// Get the counts of each card type in before and after shuffle decks 
			int G1Counts[(int)NUM_CARDS]; 
			for(n = 0; n < (int)NUM_CARDS; n++)
				G1Counts[n] = 0;
			for(m = 0; m < G1.handCount[j]; m++)
			{
				G1Counts[G1.hand[j][m]]++;
			}
			int bonus = floor(Random() * (int)NUM_CARDS);
			int sum = G1Counts[4] + (G1Counts[5] * 2) + (G1Counts[6] * 3) + bonus; 
					
			// Check the function now 
			int result = updateCoins(j, &G1, bonus);
			if(result) result = 1;
			if(sum == G1.coins)
				printf("PASSED for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
			else
			{
				printf("FAILED for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
				globalFail++;
			}
		}
		printf("\n");
	}
	
	if(globalFail > 0)
		printf("FAILED overall\n\n");
	else 
		printf("PASSED overall\n\n");
}

int main () 
{
	printf("UNIT TEST 4\n");
	updateCoinTest();
	return 0;
}