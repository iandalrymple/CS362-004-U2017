// Desc: 			Random test for fSmithy function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/20/2017
// HW4 -> CS362
// Requirements:
// 1. Current player should receive exact 3 cards and discard the smithy = net of 2 cards
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

#define NET_CARDS_TO_HAND 2
#define NET_CARDS_FROM_DECK 3

#define NUM_TESTS	50

// Oracle
void oracleSmithy(int player, int smithyIdx, int iter, struct gameState *gBefore, struct gameState *gAfter)
{	
	// Locals 
	int i = 0;
	
	// Print a NL 
	printf("\n");
	
	// Check for hand count increase of NET 2 cards
	if((gBefore -> handCount[player] + (int)NET_CARDS_TO_HAND) == gAfter -> handCount[player])
		printf("PASSED: Smithy handCount check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Smithy handCount check with before = %d and after = %d on iteration = %d.\n", 
				gBefore -> handCount[player], gAfter -> handCount[player], iter);
	
	// Check for three cards taken from his own deck 
	if((gBefore -> deckCount[player] - (int)NET_CARDS_FROM_DECK) == gAfter -> deckCount[player])
		printf("PASSED: Smithy deckCount check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Smithy deckCount check with before = %d and after = %d on iteration = %d.\n", 
				gBefore -> deckCount[player], gAfter -> deckCount[player], iter);
				
	// Check that the card that was in smithyIdx is no longer in the hand 
	int cardBefore = gBefore -> hand[player][smithyIdx];
	int beforeSmithyCount = 0;
	for(i = 0; i < gBefore -> handCount[player]; i++)
	{
		if(gBefore -> hand[player][i] == cardBefore)
			beforeSmithyCount ++;
	}
	int afterSmithyCount = 0;
	for(i = 0; i < gAfter -> handCount[player]; i++)
	{
		if(gAfter -> hand[player][i] == cardBefore)
			afterSmithyCount ++;
	}
	if(beforeSmithyCount == afterSmithyCount + 1)
		printf("PASSED: Smithy in hand count check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Smithy in hand count check with before = %d and after = %d on iteration = %d.\n", 
				beforeSmithyCount, afterSmithyCount, iter);
				
	// Copy over the changes from after to before in order to check no other changes were made 
	// But first make copy of before to preserve the state and use the copy for the comparisons
	struct gameState cpyBefore;
	memcpy (&cpyBefore, gBefore, sizeof(struct gameState));
	cpyBefore.deckCount[player] = gAfter -> deckCount[player];
	cpyBefore.discardCount[player] = gAfter -> discardCount[player];
	cpyBefore.handCount[player] = gAfter -> handCount[player];
	cpyBefore.playedCardCount = gAfter -> playedCardCount;
	for(i = 0; i < MAX_DECK; i++)
	{
		cpyBefore.deck[player][i] = gAfter -> deck[player][i];
		cpyBefore.discard[player][i] = gAfter -> discard[player][i];
		cpyBefore.playedCards[i] = gAfter -> playedCards[i];
	}
	for(i = 0; i < MAX_HAND; i++)
		cpyBefore.hand[player][i] = gAfter -> hand[player][i];
	
	// Compare the after to the before copy 
	int compare = memcmp(&cpyBefore, gAfter, sizeof(struct gameState));
	if(compare == 0)
		printf("PASSED: Smithy mutation check in iteration = %d.\n", iter);
	else
		printf("FAILED: Smithy mutation check with memcmp = %d in iteration = %d.\n", compare, iter);
}

// Entry 
// TO DO: pass the seeds in thru cl 
int main()
{
	// Locals 
	struct gameState gameBefore;
	struct gameState gameAfter;
	int i, n, p;
	i = n = p = 0;
	int smithyIdx = 0;
	
	// Seed declare 
	SelectStream(2);
	PutSeed(-1);
	
	// Print the start of test
	printf("Beginning randomtestcard2.c for Smithy\n");
	
	// Loop and run tests 
	for (n = 0; n < (int)NUM_TESTS; n++) 
	{
		// Copmpletely randomize the gamestate
		for (i = 0; i < sizeof(struct gameState); i++) 
		{
			((char*)&gameBefore)[i] = floor(Random() * 256);
		}
		
		// Set sane values for certain parameters 
		p = floor(Random() * 2);
		gameBefore.deckCount[p] = floor(Random() * MAX_DECK);
		gameBefore.discardCount[p] = floor(Random() * MAX_DECK);
		gameBefore.handCount[p] = floor(Random() * MAX_HAND);
		gameBefore.playedCards[p] = floor(Random() * MAX_DECK);
		gameBefore.playedCardCount = floor(Random() * MAX_DECK);
		
		// Copy over the state before calling smithy (memcpy 1 - dest 2 - source)
		memcpy (&gameAfter, &gameBefore, sizeof(struct gameState));
				
		// Call Smithy
		smithyIdx = floor(Random() * gameAfter.handCount[p]);
		int futResult = smithyEffect(p, smithyIdx, &gameAfter);
		if(futResult != 0)
			printf("FAILED CALL TO VILLAGE WITH RESULT %d.\n", futResult);
		
		// Call the oracle and print the results 
		oracleSmithy(p, smithyIdx, n, &gameBefore, &gameAfter);
	}
	
	// Print a NL 
	printf("\n");
	
	return 0;
}