// Desc: 			Unit test for isGameOver function in dominion.c
// Author: 			Ian Dalrymple
// Date Created: 	07/04/2017

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define		NUM_CARDS		27
#define 	NUM_REPS		50
#define 	RAND_MULT 		5

void provinceTest()
{
	int j;
	struct gameState G1;
	
	// Test with no province 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 23;
		if(j == province)
			G1.supplyCount[j] = 0;
	}	
	
	if(isGameOver(&G1) == 1)
		printf("PASSED province test with correct return equal to 1.\n");
	else
		printf("FAILED province test with incorrect return equal to 0.\n");

	// Test with province 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 14;
		if(j == province)
			G1.supplyCount[j] = 2;
	}	
	
	if(isGameOver(&G1) == 0)
		printf("PASSED province test with correct return equal to 0.\n");
	else
		printf("FAILED province test with incorrect return equal to 1.\n");
	
	printf("\n");
}

void countTest()
{
	int j; 					// Simple indexers
	int zeroCounter; 			// Count the number of zero in supply for compare to FUT
	struct gameState G1; 		// Before shuffle 
				
	// Populate the supply counts randomly but dont allow zero for province
	zeroCounter = 0;
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = 22;
		if(j == province)
			G1.supplyCount[j] = 23;
		if(j == 24 || j == 25 || j == 26)
			G1.supplyCount[j] = 0;
	}	
	
	// Now check for zeroes 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		if(G1.supplyCount[j] == 0) 
			zeroCounter++;
	}
			
	// Set zeroCounter for compare to isGameOver
	int zeroCounterPost = 0;
	if(zeroCounter >= 3)
		zeroCounterPost = 1;
	else 
		zeroCounterPost = 0;
	
	// Pass into the FUT
	if(isGameOver(&G1) == zeroCounterPost)
		printf("PASSED countTest with zeroCounter %d and isGameOver %d \n", zeroCounter, isGameOver(&G1));
	else 
	{
		printf("FAILED countTest with zeroCounter %d and isGameOver %d\n", zeroCounter, isGameOver(&G1));
		for(j = 0; j < (int)NUM_CARDS; j++)
			printf("Card %d count %d\n", j, G1.supplyCount[j]);
	}
}

int main () 
{
	printf("\nUNIT TEST 3\n");	
	provinceTest();
	countTest();
	return 0;
}

