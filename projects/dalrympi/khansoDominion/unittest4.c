// Desc: 			Unit test for updateCoins function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/06/2017
// Notes:			4, 5 and 6 are the coin cards 
// Requirements:
// 1 - must add up value of all coins in players hand and tack on the bonus passed in 
// 2 - should fail with negative reply for negative hand count 
// 3 - should not mutate the gamestate


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define		NUM_CARDS		27

// Requirement 2
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
			printf("PASSED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
	}
	printf("\n");
}

// General test and good programming 
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
			printf("PASSED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
	}
	printf("\n");
}

// Requirement 1 and 3 
void basicCountTest()
{
	int j, k;					// Simple indexers
	struct gameState G1; 		// Before shuffle 
	struct gameState G2; 		// After shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	initializeGame((int)MAX_PLAYERS, kings, 23, &G1);

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
		
		// Make a copy of the game state 
		memcpy(&G2, &G1, sizeof(struct gameState));
		
		int bonus = 1;
		int sum = 7;  
				
		// Check the function now 
		int result = updateCoins(j, &G1, bonus);
		if(result) result = 1;
		if(G1.coins < 0) 
			printf("Alert: negative coin count being returned. Verify your Dominion rule book to make sure this is allowed.\n");
		if(sum == G1.coins)
			printf("PASSED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		else
		{
			printf("FAILED: negative hand count for hand size of %d and player %d with sum of %d and bonus %d and function result %d.\n", G1.handCount[j], j, sum, bonus, G1.coins);
		}
		
		// Check to make sure nothing else is changed for this player and the other players
		G1.coins = G2.coins;
		int compareGs = gameStateCmp(&G1, &G2);
		if(compareGs != 1000)
			printf("FAILED: mutation check in basicCountTest with compare result %d.\n", compareGs);
		else 
			printf("PASSED: mutation check in basicCountTest.\n");
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