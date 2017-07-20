// Desc: 			Random test for fSmithy function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/20/2017
// HW4 -> CS362
// Requirements:
// 1. Current player should receive exact 3 cards and discard the smithy 
// 2. 3 cards should come from his own pile.
// 3. No state change should occur for other players.
// 4. No state change should occur to the victory card piles and kingdom card piles.

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

// Oracle
int oracleSmithy(int p, struct gamestate gBefore, struct gamestate gAfter)
{
	return Random() * 23;
}

// Entry 
// TO DO: pass the seeds in thru cl 
int main()
{
	// Locals 
	struct gameState gameBefore;
	struct gameState gameAfter;
	
	// Seed declare 
	SelectStream(2);
	PutSeed(3);
	
	for (n = 0; n < 2000; n++) 
	{
		for (i = 0; i < sizeof(struct gameState); i++) 
		{
			((char*)&gameBefore)[i] = floor(Random() * 256);
		}
		p = floor(Random() * 2);
		gameBefore.deckCount[p] = floor(Random() * MAX_DECK);
		gameBefore.discardCount[p] = floor(Random() * MAX_DECK);
		gameBefore.handCount[p] = floor(Random() * MAX_HAND);
					
		// Copy over the state before calling smithy (memcpy 1 - dest 2 - source)
		memcpy (&gameAfter, &gameBefore, sizeof(struct gameState));
		
		// Call the oracle and print the results 
		int result = 0;
		result = oracleSmithy(p, gameBefore, gameAfter);
		printf("Result %d\n", result);
	}
	
	return 0;
}