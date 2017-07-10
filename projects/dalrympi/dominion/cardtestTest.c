// Desc: 			Unit test for fSmithy function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/07/2017
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

#define NUM_CARDS 		27
#define TEST_HAND 		5
#define SMITHY_IDX		2
#define TEST_DECK 		100
#define TEST_DISCARD 	100

// Requirements 1 - 4
void smithyTest()
{

	struct gameState G1; 				// Before shuffle 
	int kings[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
		
	// Init the game using the presumed funtional initializeGame function
	printf("%d\n", initializeGame((int)MAX_PLAYERS, kings, 85, &G1));	
}
		
int main () 
{
	printf("\nCARD TEST 1 = SMITHY\n");
	smithyTest();
	return 0;
}