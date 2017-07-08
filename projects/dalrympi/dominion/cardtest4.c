// Desc: 			Unit test for fMine function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/08/2017

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define NUM_CARDS 		27
#define TEST_HAND 		5
#define MINE_IDX		3
#define TEST_DECK 		5
#define TEST_DISCARD 	5
#define NUM_ACTIONS		3
#define TRASH_IDX		2
#define PLAYED_COUNT	65

void checkTrashCardRule()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = 22;
			G1.deck[i][j] = 22;
			G1.discard[i][j] = 22;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Set up location of the mine 
		G1.hand[i][(int)MINE_IDX] = mine;
			
		// Call FUT - gameState, player, choice one = trash index in your hand, choice 2 = type of card seeking and 
		// hp is the hand position of the mine card which will be discarded
		int result = fMine(&G1, i, (int)TRASH_IDX, gold, (int)MINE_IDX);
		if(result > 0)
			printf("FAILED: player %d returned value greater than 0 which should be impossible.\n", i);
		else if(result == -1)
			printf("PASSED: player %d correctly bounced for not choosing copper, silver or gold to trash.\n", i);
		else 
			printf("FAILED: player %d did not bounce with incorrect card to trash.\n", i);
	}
}

void checkNewCardRule()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = copper;
			G1.deck[i][j] = copper;
			G1.discard[i][j] = copper;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Set up location of the mine 
		G1.hand[i][(int)MINE_IDX] = mine;
			
		// Call FUT - gameState, player, choice one = trash index in your hand, choice 2 = type of card seeking and 
		// hp is the hand position of the mine card which will be discarded
		int result = fMine(&G1, i, (int)TRASH_IDX, 29, (int)MINE_IDX);
		if(result > 0)
			printf("FAILED: player %d returned value greater than 0 which should be impossible.\n", i);
		else if(result == -1)
			printf("PASSED: player %d correctly bounced for choosing an invalid card for replacement card.\n", i);
		else 
			printf("FAILED: player %d did not bounce with invalid card for replacement card.\n", i);
	}
}

void checkCostRule()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = copper;
			G1.deck[i][j] = copper;
			G1.discard[i][j] = copper;
			G1.playedCards[j] = copper;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		G1.playedCardCount = (int)PLAYED_COUNT; 
		
		// Set up location of the mine 
		G1.hand[i][(int)MINE_IDX] = mine;
			
		// Call FUT - gameState, player, choice one = trash index in your hand, choice 2 = type of card seeking and 
		// hp is the hand position of the mine card which will be discarded
		int result = fMine(&G1, i, (int)TRASH_IDX, gold, (int)MINE_IDX);
		if(result > 0)
			printf("FAILED: player %d returned value greater than 0 which should be impossible.\n", i);
		else if(result == -1)
			printf("PASSED: player %d correctly bounced for choosing a replacement greater than 3 than copper.\n", i);
		else 
			printf("FAILED: player %d did not bounce when replacement card had more than 3 cost of trashed card.\n", i);
	}
}

void checkAddRule()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = copper;
			G1.deck[i][j] = copper;
			G1.discard[i][j] = copper;
			G1.playedCards[j] = copper;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		G1.playedCardCount = (int)PLAYED_COUNT; 
		
		// Set up location of the mine 
		G1.hand[i][(int)MINE_IDX] = mine;
			
		// Call FUT - gameState, player, choice one = trash index in your hand, choice 2 = type of card seeking and 
		// hp is the hand position of the mine card which will be discarded
		int result = fMine(&G1, i, (int)TRASH_IDX, gold, (int)MINE_IDX);
		if(result == 0)
		{
			int hasGold = 0;
			for(j = 0; j < G1.handCount[i]; j++)
			{	
				//printf("%d\n", G1.deck[i][j]);
				if(G1.deck[i][j] == gold)
					hasGold++;
			}
			if(hasGold > 0)
				printf("PASSED: player %d new card inserted into hand.\n", i);
			else 
				printf("FAILED: player %d new card NOT inserted into hand.\n", i);
		}
		else
			printf("FAILED: player %d new card NOT inserted into hand.\n", i);
	}
}
int main () 
{
	printf("\nCARD TEST 4 = MINE\n");
	checkTrashCardRule();
	checkNewCardRule();
	checkCostRule();
	checkAddRule();
	return 0;
}