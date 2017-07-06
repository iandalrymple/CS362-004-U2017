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

void shuffleDeckEmptyTest()
{
	int j; 						// Simple indexer
	struct gameState G1; 		
	
	// Introduction
	printf("Testing empty deck.\n");
	
	// Check to make sure it bombs out for no cards in deck
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		G1.deckCount[j] = 0;
		if(shuffle(j, &G1) == -1)
			printf("PASSED init count check for player %d with count of %d.\n", j, 0);
		else
			printf("FAILED init count check for player %d.\n", j);
	}
	
	// Check to make sure it bombs out for no cards in deck
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

void shuffleCountRandomTest()
{
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 
	int masterPassFailFlag = 0; // Master flag for entire test 
	
	// Vary deck size in increments of 50
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{	
		// Inform user of test being performed 
		printf("Testing deck size of %d for equal counts and randomness.\n", i);
		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Get random stream and seed with time based 
			SelectStream(j);
			PutSeed(-1);
		
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.deck[j][k] = floor(Random() * 27);
				G2.deck[j][k] = G1.deck[j][k];
			}
			
			// Set the deck count 
			int deckCount = 0;
			if(i < MAX_DECK)
			{
				G1.deckCount[j] = G2.deckCount[j] = i;
				deckCount = i;
			}
			else
			{
				G1.deckCount[j] = G2.deckCount[j] = MAX_DECK;
				deckCount = MAX_DECK;
			}

			// Shuffle the deck 
			int result = shuffle(j, &G2);
			if(result < -1) 
				printf("PLAYER HAS NO CARDS LEFT IN DECK - SHOULD NOT HAPPEN.\n");		
			
			// Get the counts of each card type in before and after shuffle decks 
			int G1Counts[27]; 
			int G2Counts[27];
			for(n = 0; n < 27; n++)
				G1Counts[n] = G2Counts[n] = 0;
			for(m = 0; m < deckCount; m++)
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
					printf("FAILED Deck size = %d Player = %d CardValue = %d CardCountRaw = %d, CardCountShuffle = %d.\n", deckCount, j, p, G1Counts[p], G2Counts[p]);
					countFlag++;
					masterPassFailFlag++;
				}
			}
					
			// Check to make sure the cards are shuffled ISH
			int mixCounter = 0;
			for(m = 0; m < deckCount; m++)
			{
				if(G1.deck[j][m] != G2.deck[j][m])
				{
					mixCounter++;
				}
			}
			if(mixCounter == 0)
				masterPassFailFlag++;
			
			// Print out the final result 
			if(mixCounter > 0 && countFlag == 0)
				printf("PASSED for deck size of %d and player %d for bin count and randomness check.\n", deckCount, j);
			else 
				printf("FAILED for deck size of %d and player %d with countFlag = %d and randomFlag = %d.\n", i, j, countFlag, mixCounter);				
		}
		
		printf("\n");
	}
	
	// Present the master results for all tests
	if(masterPassFailFlag == 0)
		printf("PASSED count and randomness testing.\n");
	else
		printf("FAILED count and randomness testing with %d errors.\n", masterPassFailFlag);
}

int main () 
{
	shuffleDeckEmptyTest();
	shuffleCountRandomTest();
	return 0;
}

