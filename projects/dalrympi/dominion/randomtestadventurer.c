// Desc: 			Random test for fAdventurer function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/21/2017
// Card Requirements:
// 1 - treasure in hand increased by 2 
// 2 - adventurer is kept in hand 
// 3 - cards drawn that are not treasure sent to discard pile deltaDisCard = dDrawn - 2
// 4 - other players not mutated 
// 5 - other attributes beyond deck, hand, discard played are not mutated 

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
#define TREASURE_INCREASE 2 

// Oracle
void oracleAdventurer(int player, int iter, struct gameState *gBefore, struct gameState *gAfter)
{	
	// Locals 
	int i = 0;
	
	// Print a NL 
	printf("\n");
	
	// Check for two more treasures
	int beforeTreasure = 0;
	for(i = 0; i < gBefore -> handCount[player]; i++)
	{
		if(gBefore -> hand[player][i] == copper || 
					gBefore -> hand[player][i] == silver || 
					gBefore -> hand[player][i] == gold)
			beforeTreasure ++;
	}
	int afterTreasure = 0;
	for(i = 0; i < gAfter -> handCount[player]; i++)
	{
		if(gAfter -> hand[player][i] == copper || 
					gAfter -> hand[player][i] == silver || 
					gAfter -> hand[player][i] == gold)
			afterTreasure ++;
	}
		
	if(afterTreasure == beforeTreasure + (int)TREASURE_INCREASE)
		printf("PASSED: Adventurer treasure count check in iteration = %d.\n", iter);
	else 
		printf("FAILED: Adventurer treasure count check with before = %d and after = %d on iteration = %d.\n", 
				beforeTreasure, afterTreasure, iter);
	return;
	
	// // Check for one card taken from his own deck 
	// if((gBefore -> deckCount[player] - (int)NET_CARDS_FROM_DECK) == gAfter -> deckCount[player])
		// printf("PASSED: Village deckCount check in iteration = %d.\n", iter);
	// else 
		// printf("FAILED: Village deckCount check with before = %d and after = %d on iteration = %d.\n", 
				// gBefore -> deckCount[player], gAfter -> deckCount[player], iter);
	
	// // Check for hand count to stay the same 
	// if(gBefore -> handCount[player] == gAfter -> handCount[player])
		// printf("PASSED: Village handCount check in iteration = %d.\n", iter);
	// else 
		// printf("FAILED: Village handCount check with before = %d and after = %d on iteration = %d.\n", 
				// gBefore -> handCount[player], gAfter -> handCount[player], iter);
				
	// // Check that the card that was in villageIdx is no longer in the hand 
	// int cardBefore = gBefore -> hand[player][villageIdx];
	// int beforeVillageCount = 0;
	// for(i = 0; i < gBefore -> handCount[player]; i++)
	// {
		// if(gBefore -> hand[player][i] == cardBefore)
			// beforeVillageCount ++;
	// }
	// int afterVillageCount = 0;
	// for(i = 0; i < gAfter -> handCount[player]; i++)
	// {
		// if(gAfter -> hand[player][i] == cardBefore)
			// afterVillageCount ++;
	// }
	// if(beforeVillageCount == afterVillageCount + 1)
		// printf("PASSED: Village in hand count check in iteration = %d.\n", iter);
	// else 
		// printf("FAILED: Village in hand count check with before = %d and after = %d on iteration = %d.\n", 
				// beforeVillageCount, afterVillageCount, iter);
				
	// // Copy over the changes from after to before in order to check no other changes were made 
	// // But first make copy of before to preserve the state and use the copy for the comparisons
	// struct gameState cpyBefore;
	// memcpy (&cpyBefore, gBefore, sizeof(struct gameState));
	// cpyBefore.numActions = gAfter -> numActions;
	// cpyBefore.deckCount[player] = gAfter -> deckCount[player];
	// cpyBefore.discardCount[player] = gAfter -> discardCount[player];
	// cpyBefore.handCount[player] = gAfter -> handCount[player];
	// cpyBefore.playedCardCount = gAfter -> playedCardCount;
	// for(i = 0; i < MAX_DECK; i++)
	// {
		// cpyBefore.deck[player][i] = gAfter -> deck[player][i];
		// cpyBefore.discard[player][i] = gAfter -> discard[player][i];
		// cpyBefore.playedCards[i] = gAfter -> playedCards[i];
	// }
	// for(i = 0; i < MAX_HAND; i++)
		// cpyBefore.hand[player][i] = gAfter -> hand[player][i];
	
	// // Compare the after to the before copy 
	// int compare = memcmp(&cpyBefore, gAfter, sizeof(struct gameState));
	// if(compare == 0)
		// printf("PASSED: Village mutation check in iteration = %d.\n", iter);
	// else
		// printf("FAILED: Village mutation check with memcmp = %d in iteration = %d.\n", compare, iter);
}

// Entry 
int main()
{
	// Locals 
	struct gameState gameBefore;
	struct gameState gameAfter;
	int i, n, p;
	i = n = p = 0;
	
	// Seed declare 
	SelectStream(2);
	PutSeed(3);
	
	// Print the start of test
	printf("Beginning randomtestadventurer.c for Adventurer\n");
	
	// Loop and run tests 
	for (n = 0; n < 5; n++) 
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
		
		// Seed the deck with five additional treasures 
		int idx = -99;
		if(gameBefore.deckCount[p] > 0)
		{
			idx = (int)(floor(Random() * gameBefore.deckCount[p]));
			for(i = 0; i < 5; i++)
				gameBefore.deck[p][idx] = (int)(floor(Random() * 3)) + 4;
		}
		else
		{
			idx = (int)(floor(Random() * gameBefore.discardCount[p]));
			for(i = 0; i < 5; i++)
				gameBefore.discard[p][idx] = (int)(floor(Random() * 3)) + 4;
		}

		// Copy over the state before calling smithy (memcpy 1 - dest 2 - source)
		memcpy (&gameAfter, &gameBefore, sizeof(struct gameState));
				
		// Call Adventurer
		int futResult = fAdventurer(&gameAfter, p);
		if(futResult != 0)
			printf("FAILED CALL TO ADVENTURER WITH RESULT %d.\n", futResult);
		
		// Call the oracle and print the results 
		// oracleAdventurer(p, n, &gameBefore, &gameAfter);
	}
	
	// Print a NL 
	printf("\n");
	
	return 0;
}