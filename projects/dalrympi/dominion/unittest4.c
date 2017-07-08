// Desc: 			Unit test for updateCoins function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/06/2017
// Notes:			4, 5 and 6 are the coin cards 

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define		NUM_CARDS		27

void negativeHandCountTest()
{
	int j, k;					// Simple indexers
	struct gameState G1; 		// Before shuffle 

	
	// Assign each player 
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		// Assign the card values 
		for(k = 0; k < MAX_DECK; k++)
		{
			G1.hand[j][k] = 4;
		}
		
		// Set the hand count 
		G1.handCount[j] = -3;
		
		int bonus = 22;
		int sum = 22; // Really undefined cause we dont have any cards to speak of 
				
		// Check the function now 
		int result = updateCoins(j, &G1, bonus);
		if(result) result = 1;
		if(G1.coins < 0) 
			printf("Alert: negative coin count being returned. Verify your Dominion rule book to make sure this is allowed.\n");
		if(sum == G1.coins)
			printf("PASSED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
	}
	printf("\n");
}

void negativeBonusTest()
{
	int j, k;					// Simple indexers
	struct gameState G1; 		// Before shuffle 

	// Assign each player 
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		// Assign the card values 
		for(k = 0; k < MAX_DECK; k++)
		{
			G1.hand[j][k] = 4;
		}
		
		// Set the hand count 
		G1.handCount[j] = 6;
		
		int bonus = -45;
		int sum = 6 - 45;  
				
		// Check the function now 
		int result = updateCoins(j, &G1, bonus);
		if(result) result = 1;
		if(G1.coins < 0) 
			printf("Alert: negative coin count being returned. Verify your Dominion rule book to make sure this is allowed.\n");
		if(sum == G1.coins)
			printf("PASSED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
	}
	printf("\n");
}

void basicCountTest()
{
	int j, k;					// Simple indexers
	struct gameState G1; 		// Before shuffle 

	// Assign each player 
	for(j = 0; j < MAX_PLAYERS; j++)
	{
		// Assign the card values 
		for(k = 0; k < MAX_DECK; k++)
		{
			G1.hand[j][k] = 4;
		}
		
		G1.hand[j][0] = 4;
		G1.hand[j][1] = 5;
		G1.hand[j][2] = 6;
		
		// Set the hand count 
		G1.handCount[j] = 3;
		
		int bonus = 1;
		int sum = 7;  
				
		// Check the function now 
		int result = updateCoins(j, &G1, bonus);
		if(result) result = 1;
		if(G1.coins < 0) 
			printf("Alert: negative coin count being returned. Verify your Dominion rule book to make sure this is allowed.\n");
		if(sum == G1.coins)
			printf("PASSED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
	}
}

int main () 
{
	printf("\nUNIT TEST 4\n");
	negativeHandCountTest();
	negativeBonusTest();
	basicCountTest();
	return 0;
}