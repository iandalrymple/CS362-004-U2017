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
#define 	NUM_REPS		20
#define 	RAND_MULT 		5

void provinceTest()
{
	int j;
	struct gameState G1;
	
	// Test with no province 
	for(j = 0; j < (int)NUM_CARDS; j++)
	{
		G1.supplyCount[j] = floor(Random() * (int)RAND_MULT) + 1;
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
		G1.supplyCount[j] = floor(Random() * (int)RAND_MULT) + 1;
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
	int i, j; 					// Simple indexers
	int zeroCounter; 			// Count the number of zero in supply for compare to FUT
	int globalFlag = 0; 		// 0 = passed and GTE 1 = fail 
	struct gameState G1; 		// Before shuffle 
	
	// Set up the random seeding 
	SelectStream(99);
	PutSeed(-1);
	
	// Run x iterations possibly passed in via csh
	for(i = 0; i < (int)NUM_REPS; i++)
	{			
		// Populate the supply counts randomly but dont allow zero for province
		zeroCounter = 0;
		for(j = 0; j < (int)NUM_CARDS; j++)
		{
			G1.supplyCount[j] = floor(Random() * (int)RAND_MULT);
			if(j == province)
				G1.supplyCount[j] = floor(Random() * (int)RAND_MULT) + 1;
			if(G1.supplyCount[j] == 0) 
				zeroCounter++;		
			//printf("Card %d count %d\n", j, G1.supplyCount[j]);
		}	
				
		// Set zeroCounter for compare to isGameOver
		if(zeroCounter >= 3)
			zeroCounter = 1;
		else 
			zeroCounter = 0;
		
		// Pass into the FUT
		if(isGameOver(&G1) == zeroCounter)
			printf("PASSED iteration %d in countTest with zeroCounter %d and isGameOver %d \n", i, zeroCounter, isGameOver(&G1));
		else 
		{
			printf("FAILED iteration %d in countTest with zeroCounter %d and isGameOver %d\n", i, zeroCounter, isGameOver(&G1));
			globalFlag++;
			for(j = 0; j < (int)NUM_CARDS; j++)
				printf("Card %d count %d on iteration %d\n", j, G1.supplyCount[j], i);
		}
	}
	
	// Pass into the FUT
	if(globalFlag == 0)
		printf("PASSED count test\n\n");
	else 
		printf("FAILED count test\n\n");
}

int main () 
{
	printf("UNIT TEST 3\n");	
	provinceTest();
	countTest();
	return 0;
}

