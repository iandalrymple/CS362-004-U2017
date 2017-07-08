// Desc: 			Unit test for fadventurer function in dominion.c
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
#define ADV_IDX			2
#define TEST_DECK 		5
#define TEST_DISCARD 	5

void treasureCount()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = 5;
			G1.deck[i][j] = 5;
			G1.discard[i][j] = 5;
		}
		
		// Insert the adventurer
		G1.hand[i][(int)ADV_IDX] = adventurer;
		
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Call fadventurer
		if(fAdventurer(&G1, i))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] == 7)
			printf("PASSED: player %d handcount tested correctly equal to 7.\n", i);
		else 
			printf("FAILED: player %d handcount incorrectly equal to %d.\n", i, G1.handCount[i]);	

		// for(j = 0; j < 10; j++)
			// printf("%d \n", G1.hand[i][j]);
	}
}

void noAdvTest()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = 5;
			G1.deck[i][j] = 5;
			G1.discard[i][j] = 5;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Call fadventurer
		if(fAdventurer(&G1, i))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] != (int)TEST_HAND)
			printf("FAILED: player %d did not havea an adventurer and still performed function and card adds.\n", i);
		else 
			printf("PASSED: player %d no adventurer so nothing happened correctly.\n", i);	
	}
}

void currentPlayerTest()
{
	struct gameState G1; // Working 
	int i, j;

	// Test each player
	for(i = 0; i < MAX_PLAYERS; i++)
	{
		// Assign the card values to hand, deck and supply 
		for(j = 0; j < MAX_DECK; j++)
		{
			G1.hand[i][j] = 5;
			G1.deck[i][j] = 5;
			G1.discard[i][j] = 5;
		}
			
		// Set up counts 
		G1.handCount[i] = (int)TEST_HAND;
		G1.deckCount[i] = (int)TEST_DECK;
		G1.discardCount[i] = (int)TEST_DISCARD;
		
		// Call fadventurer
		if(fAdventurer(&G1, 6))
			printf("FAILED: player %d returned value greater than 0 which means something went wrong.\n", i);
		
		// Check the hand count 
		if(G1.handCount[i] != (int)TEST_HAND)
			printf("FAILED: player %d bad player passed in and still performed function.\n", i);
		else 
			printf("PASSED: player %d bad player and function did not execute which is correct.\n", i);	
	}
}
	
int main () 
{
	printf("\nCARD TEST 2 = ADVENTURER\n");
	treasureCount();
	noAdvTest();
	currentPlayerTest();
	return 0;
}