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
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 
	int masterPassFailFlag = 0; // Master flag for entire test 
	
	// Get random stream and seed with time based 
	SelectStream(123);
	PutSeed(-1);
		
	// Vary deck size in increments of 50 and test 2,3,2,3
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				if(k % 2 == 0)
					G1.deck[j][k] = 2;
				else 
					G1.deck[j][k] = 3;
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
	
	// Vary deck size in increments of 50 and test 0,1,2,3,4,5,...... 26
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.deck[j][k] = k % (int)NUM_CARDS;
				G2.deck[j][k] = G1.deck[j][k];
				// printf("%d %d \n", k, G1.deck[j][k]);
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
	
	// Vary deck size in increments of 50 and test reverse 26, 25, 24, 23, 22, ..... 0
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.deck[j][k] = ((int)NUM_CARDS - 1)  - (k % (int)NUM_CARDS);
				G2.deck[j][k] = G1.deck[j][k];
				// printf("%d %d \n", k, G1.deck[j][k]);
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
		printf("PASSED count and randomness testing.\n\n");
	else
		printf("FAILED count and randomness testing with %d errors.\n\n", masterPassFailFlag);
}

int main () 
{
	printf("UNIT TEST 1\n");
	shuffleDeckEmptyTest();
	shuffleCountTest();
	return 0;
}

