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
			}
			
			// Set the deck count 
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
			int countFlag = 0;
			for(p = 0; p < 27; p++)
			{
				if(G1Counts[p] != fullDeckCount(j, p, &G1))
				{
					printf("FAILED Deck size = %d Player = %d CardValue = %d Actual Count = %d, fullDeckCount = %d.\n", deckCount, j, p, G1Counts[p], fullDeckCount(j, p, &G1));
				}
			}		
		}
		
		printf("\n");
	}
}

int main () 
{
	deckCountTest();
	return 0;
}

