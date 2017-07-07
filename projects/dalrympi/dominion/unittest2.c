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

void deckCountTest()
{
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; // Master flag for entire test 
	
	// Get random stream and seed with time based 
	SelectStream(56);
	PutSeed(-1);
	
	// Vary deck size in increments of 50
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{		
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.deck[j][k] = floor(Random() * 27);
			}
			
			// Set the counts 
			G1.handCount[j] = 0;
			G1.discardCount[j] = 0;
			int deckCount = 0;
			if(i < MAX_DECK)
			{
				G1.deckCount[j] = i;
				deckCount = i;
			}
			else
			{
				G1.deckCount[j] = MAX_DECK;
				deckCount = MAX_DECK;
			}
			
			// Get the counts of each card type in before and after shuffle decks 
			int G1Counts[27]; 
			for(n = 0; n < 27; n++)
				G1Counts[n] = 0;
			for(m = 0; m < deckCount; m++)
			{
				G1Counts[G1.deck[j][m]]++;
				//printf("Deck size = %d Player = %d CardIdx = %d Before = %d and after = %d\n", deckCount, j, m, G1.deck[j][m], G2.deck[j][m]);
			}
			
			// Compare the counts - should be equal 
			int failFlag = 0;
			for(p = 0; p < 27; p++)
			{
				if(G1Counts[p] != fullDeckCount(j, p, &G1))
				{
					printf("FAILED Deck size = %d Player = %d CardValue = %d Actual Count = %d, fullDeckCount = %d.\n", deckCount, j, p, G1Counts[p], fullDeckCount(j, p, &G1));
					failFlag++;
					globalFlag++;
				}
			}

			if(failFlag > 0)
				printf("FAILED deck size %d for player = %d.\n", deckCount, j);
			else
				printf("PASSED deck size %d for player = %d.\n", deckCount, j);
		}
		printf("\n");
	}
	
	if(globalFlag > 0)
		printf("FAILED deck count check test.\n\n");
	else
		printf("PASSED deck count check test.\n\n");
}

void handCountTest()
{
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; // Master flag for entire test 
	
	// Get random stream and seed with time based 
	SelectStream(37);
	PutSeed(-1);
	
	// Vary deck size in increments of 50
	for(i = 50; i < MAX_HAND + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{	
			// Assign the card values 
			for(k = 0; k < MAX_HAND; k++)
			{
				G1.hand[j][k] = floor(Random() * 27);
			}
			
			// Set the counts 
			int handCount = 0;
			G1.deckCount[j] = 0;
			G1.discardCount[j] = 0;
			if(i < MAX_DECK)
			{
				G1.handCount[j] = i;
				handCount = i;
			}
			else
			{
				G1.handCount[j] = MAX_HAND;
				handCount = MAX_HAND;
			}
			
			// Get the counts of each card type in before and after shuffle decks 
			int G1Counts[27]; 
			for(n = 0; n < 27; n++)
				G1Counts[n] = 0;
			for(m = 0; m < handCount; m++)
			{
				G1Counts[G1.hand[j][m]]++;
			}
			
			// Compare the counts - should be equal 
			int failFlag = 0;
			for(p = 0; p < 27; p++)
			{
				if(G1Counts[p] != fullDeckCount(j, p, &G1))
				{
					printf("FAILED Hand size = %d Player = %d CardValue = %d Actual Count = %d, fullDeckCount = %d.\n", handCount, j, p, G1Counts[p], fullDeckCount(j, p, &G1));
					failFlag++;
					globalFlag++;
				}
			}

			if(failFlag > 0)
				printf("FAILED hand size %d for player = %d.\n", handCount, j);
			else
				printf("PASSED hand size %d for player = %d.\n", handCount, j);
		}
		printf("\n");
	}
	
	if(globalFlag > 0)
		printf("FAILED hand count check test.\n\n");
	else
		printf("PASSED hand count check test.\n\n");
}

void discardCountTest()
{
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	// Get random stream and seed with time based 
	SelectStream(88);
	PutSeed(-1);
	
	// Vary deck size in increments of 50
	for(i = 50; i < MAX_DECK + 1; i = i + 50)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{	
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.discard[j][k] = floor(Random() * 27);
			}
			
			// Set the counts 
			G1.handCount[j] = 0;
			G1.deckCount[j] = 0;
			int discardCount = 0;
			if(i < MAX_DECK)
			{
				G1.discardCount[j] = i;
				discardCount = i;
			}
			else
			{
				G1.discardCount[j] = MAX_DECK;
				discardCount = MAX_DECK;
			}
			
			// Get the counts of each card type in before and after shuffle decks 
			int G1Counts[27]; 
			for(n = 0; n < 27; n++)
				G1Counts[n] = 0;
			for(m = 0; m < discardCount; m++)
			{
				G1Counts[G1.discard[j][m]]++;
				//printf("Deck size = %d Player = %d CardIdx = %d Before = %d and after = %d\n", deckCount, j, m, G1.deck[j][m], G2.deck[j][m]);
			}
			
			// Compare the counts - should be equal 
			int failFlag = 0;
			for(p = 0; p < 27; p++)
			{
				if(G1Counts[p] != fullDeckCount(j, p, &G1))
				{
					printf("FAILED discard size = %d Player = %d CardValue = %d Actual Count = %d, fullDeckCount = %d.\n", discardCount, j, p, G1Counts[p], fullDeckCount(j, p, &G1));
					failFlag++;
					globalFlag++;
				}
			}

			if(failFlag > 0)
				printf("FAILED discard size %d for player = %d.\n", discardCount, j);
			else
				printf("PASSED discard size %d for player = %d.\n", discardCount, j);
		}
		printf("\n");
	}
	
	if(globalFlag > 0)
		printf("FAILED discard count check test.\n\n");
	else
		printf("PASSED discard count check test.\n\n");
}

void allCountTest()
{
	int i, j, k, m, n, p; 		// Simple indexers
	struct gameState G1; 		// Before shuffle 
	int globalFlag = 0; 		// Master flag for entire test 
	
	// Get random stream and seed with time based 
	SelectStream(21);
	PutSeed(-1);
			
	// Perform 10 iterations of random combinations of deck, hand and discard sizes 
	for(i = 0; i < 10; i++)
	{		
		// Assign each player 
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			// Assign the card values 
			for(k = 0; k < MAX_DECK; k++)
			{
				G1.deck[j][k] = floor(Random() * 27);
				G1.hand[j][k] = floor(Random() * 27);
				G1.discard[j][k] = floor(Random() * 27);
			}
			
			// Set the counts 
			G1.deckCount[j] = floor(Random() * 495) + 1;
			G1.handCount[j] = floor(Random() * 495) + 1;
			G1.discardCount[j] = floor(Random() * 495) + 1;
			
			// Get the counts of each card type before and after shuffle decks 
			int G1Counts[27]; 
			for(n = 0; n < 27; n++)
				G1Counts[n] = 0;
			for(m = 0; m < G1.deckCount[j]; m++)
			{
				G1Counts[G1.deck[j][m]]++;
			}
			for(m = 0; m < G1.handCount[j]; m++)
			{
				G1Counts[G1.hand[j][m]]++;
			}
			for(m = 0; m < G1.discardCount[j]; m++)
			{
				G1Counts[G1.discard[j][m]]++;
			}
			
			// Compare the counts - should be equal 
			int failFlag = 0;
			for(p = 0; p < 27; p++)
			{
				if(G1Counts[p] != fullDeckCount(j, p, &G1))
				{
					printf("FAILED player = %d CardValue = %d Actual Count = %d, fullDeckCount = %d.\n", j, p, G1Counts[p], fullDeckCount(j, p, &G1));
					failFlag++;
					globalFlag++;
				}
			}

			if(failFlag > 0)
				printf("FAILED all for player = %d on iteration %d.\n", j, i);
			else
				printf("PASSED all for player = %d on iteration %d.\n", j, i);
		}
		printf("\n");
	}
	
	if(globalFlag > 0)
		printf("FAILED all count check test.\n\n");
	else
		printf("PASSED all count check test.\n\n");
}

int main () 
{
	printf("UNIT TEST 2.\n");
	deckCountTest();
	handCountTest();
	discardCountTest();
	allCountTest();
	return 0;
}

