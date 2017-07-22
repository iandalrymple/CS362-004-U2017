// Desc: 			Random test for fVillage function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/21/2017
// HW4 -> CS362
// Requirements:
// 1 - gain two actions 
// 2 - gain a card from deck 
// 3 - gain a card to hand
// 4 - do not mutate any other players or any other features of the active player
// 5 - get rid of the village card to discard pile 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NET_CARDS_TO_HAND 0
#define NET_CARDS_FROM_DECK 1
#define NET_CARDS_TO_DISCARD 1
#define ACTION_INCREASE 2 

// Oracle
void oracleVillage(int player, int villageIdx, int iter, struct gameState *gBefore, struct gameState *gAfter)
{	
	// Locals 
	int i = 0;
	
	// Print a NL 
	printf("\n");
	
	// Check for two more actions 
	if((gBefore -> numActions + (int)ACTION_INCREASE) == gAfter -> numActions)
		printf("PASSED: Village action check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Village action check with before = %d and after = %d on iteration = %d.\n", 
				gBefore -> numActions, gAfter -> numActions, iter);
	
	// Check for one card taken from his own deck 
	if((gBefore -> deckCount[player] - (int)NET_CARDS_FROM_DECK) == gAfter -> deckCount[player])
		printf("PASSED: Village deckCount check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Village deckCount check with before = %d and after = %d on iteration = %d.\n", 
				gBefore -> deckCount[player], gAfter -> deckCount[player], iter);
	
	// Check for hand count to stay the same 
	if(gBefore -> handCount[player] == gAfter -> handCount[player])
		printf("PASSED: Village handCount check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Village handCount check with before = %d and after = %d on iteration = %d.\n", 
				gBefore -> handCount[player], gAfter -> handCount[player], iter);
				
	// Check that the card that was in villageIdx is no longer in the hand 
	int cardBefore = gBefore -> hand[player][villageIdx];
	int beforeVillageCount = 0;
	for(i = 0; i < gBefore -> handCount[player]; i++)
	{
		if(gBefore -> hand[player][i] == cardBefore)
			beforeVillageCount ++;
	}
	int afterVillageCount = 0;
	for(i = 0; i < gAfter -> handCount[player]; i++)
	{
		if(gAfter -> hand[player][i] == cardBefore)
			afterVillageCount ++;
	}
	if(beforeVillageCount == afterVillageCount + 1)
		printf("PASSED: Village in hand count check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Village in hand count check with before = %d and after = %d on iteration = %d.\n", 
				beforeVillageCount, afterVillageCount, iter);
				
	// Copy over the changes from after to before in order to check no other changes were made 
	// But first make copy of before to preserve the state and use the copy for the comparisons
	struct gameState cpyBefore;
	memcpy (&cpyBefore, gBefore, sizeof(struct gameState));
	cpyBefore.numActions = gAfter -> numActions;
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
		printf("PASSED: Village mutation check in iteration = %d.\n", iter);
	else
		printf("FAILED: Village mutation check with memcmp = %d in iteration = %d.\n", compare, iter);
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
	int villageIdx = 0;
	
	// Seed declare 
	SelectStream(2);
	PutSeed(3);
	
	// Print the start of test
	printf("Beginning randomtestcard1.c for Village\n");
	
	// Loop and run tests 
	for (n = 0; n < 1000; n++) 
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
				
		// Call Village
		villageIdx = floor(Random() * gameAfter.handCount[p]);
		int futResult = fVillage(&gameAfter, p, villageIdx);
		if(futResult != 0)
			printf("FAILED CALL TO VILLAGE WITH RESULT %d.\n", futResult);
		
		// Call the oracle and print the results 
		oracleVillage(p, villageIdx, n, &gameBefore, &gameAfter);
	}
	
	// Print a NL 
	printf("\n");
	
	return 0;
}