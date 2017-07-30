CFLAGS = -Wall -fpic -coverage -lm
CFLAGS_HW3 = -Wall

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)
	
interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

## HW 3 Unit Tests
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	
unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	
unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
unittestresults.out: unittest1.c unittest2.c unittest3.c unittest4.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./unittest1 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./unittest2 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./unittest3 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./unittest4 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./cardtest1 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./cardtest2 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./cardtest3 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	./cardtest4 &>> unittestresults.out
	gcov -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

all: playdom player unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 unittestresults.out

clean:
	rm -f *.o *.gcov *.gcda *.gcno *.so *.out playdom player badTestDrawCard testDrawCard 
	rm -f unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 demoTest 
	rm -f randomtestcard1 randomtestcard2 randomtestadventurer
	
## HW 4 Random Tests
hw4: randomtestadventurer.out randomtestcard1.out randomtestcard2.out

randomtestadventurer.out: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer &>> randomtestadventurer.out
	gcov -b -c dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 &>> randomtestcard1.out
	gcov -b -c dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 &>> randomtestcard2.out
	gcov -b -c dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
## Old tests that do not work all too well 
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

demoTest: cardtestTest.c dominion.o rngs.o
	gcc -o demoTest -g  cardtestTest.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	
## HW 5 builds - do not include the .out files which are not required per spec doc
Hw_5: clean Hw_5_unit Hw_5_card Hw_5_random
Hw_5_unit: unittest1_Hw5 unittest2_Hw5 unittest3_Hw5 unittest4_Hw5  
Hw_5_card: cardtest1_Hw5 cardtest2_Hw5 cardtest3_Hw5 cardtest4_Hw5
Hw_5_random: randomtestadventurer_Hw5 randomtestcard1_Hw5 randomtestcard2_Hw5

unittest1_Hw5: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	./unittest1

unittest2_Hw5: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	./unittest2
	
unittest3_Hw5: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	./unittest3
	
unittest4_Hw5: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	./unittest4
	
cardtest1_Hw5: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	./cardtest1
	
cardtest2_Hw5: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
	./cardtest2
	
cardtest3_Hw5: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	./cardtest3
	
cardtest4_Hw5: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	./cardtest4

randomtestadventurer_Hw5: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer &>> randomtestadventurer.out

randomtestcard1_Hw5: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 &>> randomtestcard1.out

randomtestcard2_Hw5: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 &>> randomtestcard2.out








