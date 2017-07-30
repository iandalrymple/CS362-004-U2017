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

#define NUM_TESTS	1000
#define MAX_CARDS 	249

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
	
	// Check that the Adventurer is still in hand. We can only check that the hand 
	// is the same with the addition of X number of treasures
	int diffCardFlag = 0;
	for(i = 0; i < gBefore -> handCount[player]; i++)
	{
		if(gBefore -> hand[player][i] != gAfter -> hand[player][i])
			diffCardFlag ++;
	}
	if(diffCardFlag == 0)
		printf("PASSED: Adventurer card still in hand iteration = %d.\n", iter);
	else 
		printf("FAILED: Adventurer card has potentially been removed with %d diffs on iteration = %d.\n", diffCardFlag, iter);
	
	// Check that the cards taken from deck that are not treasure are sent to discard pile 
	int deltaDeck = gBefore -> deckCount[player] - gAfter -> deckCount[player];
	int deltaDiscard = gAfter -> discardCount[player] - gBefore -> discardCount[player];
	int deltaHand = gAfter -> handCount[player] - gBefore -> handCount[player];
	if(deltaDeck == (deltaDiscard + deltaHand))
		printf("PASSED: Drawn cards that are not treasure are sent to discard in hand on iteration = %d.\n", iter);
	else 
		printf("FAILED: Drawn cards NOT reconciled with deltaDeck = %d, deltaDiscard = %d and deltaHand = %d on iteration = %d.\n", deltaDeck, deltaDiscard, deltaHand, iter);
				
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
		printf("PASSED: Adventurer mutation check in iteration = %d.\n", iter);
	else
		printf("FAILED: Adventurer mutation check with memcmp = %d in iteration = %d.\n", compare, iter);
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
	PutSeed(-1);
	
	// Print the start of test
	printf("Beginning randomtestadventurer.c for Adventurer\n");
	
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
		gameBefore.deckCount[p] = floor(Random() * MAX_CARDS);
		gameBefore.discardCount[p] = floor(Random() * MAX_CARDS);
		gameBefore.handCount[p] = floor(Random() * MAX_CARDS);
		gameBefore.playedCards[p] = floor(Random() * MAX_CARDS);
		gameBefore.playedCardCount = floor(Random() * MAX_CARDS);
		
		// Deck and discard of zero will seg fault so fix that 
		if(gameBefore.deckCount[p] == 0 && gameBefore.discardCount[p] == 0)
		{
			if(floor(Random() * 2) == 1)
				gameBefore.deckCount[p] = floor(Random() * MAX_CARDS) + 25;
			else 
				gameBefore.discardCount[p] = floor(Random() * MAX_CARDS) + 25;
		}
		
		// Seed with some 0 deck sizes to get coverage of branch in FUT 
		// Simple manual seeding that prevents the need to run a million tests
		// if(n > NUM_TESTS - floor(.1 * (int)NUM_TESTS))
			// gameBefore.deckCount[p] = 0;
			
		// Seed the deck with five additional treasures 
		int idx = -99;
		if(gameBefore.deckCount[p] > 0)
		{		
			for(i = 0; i < 5; i++)
			{
				idx = (int)(floor(Random() * gameBefore.deckCount[p]));
				gameBefore.deck[p][idx] = (int)(floor(Random() * 3)) + 4;
			}
		}
		else
		{
			for(i = 0; i < 5; i++)
			{
				idx = (int)(floor(Random() * gameBefore.discardCount[p]));
				gameBefore.discard[p][idx] = (int)(floor(Random() * 3)) + 4;
			}
		}

		// Copy over the state before calling smithy (memcpy 1 - dest 2 - source)
		memcpy (&gameAfter, &gameBefore, sizeof(struct gameState));
				
		// Call Adventurer	
		int futResult = adventurerEffect(p, 33, &gameAfter);
		if(futResult != 0)
			printf("FAILED CALL TO ADVENTURER WITH RESULT %d.\n", futResult);
		
		// Call the oracle and print the results 
		oracleAdventurer(p, n, &gameBefore, &gameAfter);
	}
	
	// Print a NL 
	printf("\n");
	
	return 0;
}