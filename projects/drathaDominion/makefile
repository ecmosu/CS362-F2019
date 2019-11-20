CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testdrawcard: testdrawcard.c dominion.o rngs.o
	gcc -o testdrawcard -g  testdrawcard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testdrawcard 
	./testdrawcard &> unittestresult.out
	gcov dominion.c -b -f >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.ut *.rt *.gcov *.gcda *.gcno *.so *.out testdrawcard testdrawcard.exe


unittestresults: clean unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c dominion.o rngs.o
	gcc  -o unittest1.ut -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	gcc  -o unittest2.ut -g  unittest2.c dominion.o rngs.o $(CFLAGS)
	gcc  -o unittest3.ut -g  unittest3.c dominion.o rngs.o $(CFLAGS)
	gcc  -o unittest4.ut -g  unittest4.c dominion.o rngs.o $(CFLAGS)
	gcc  -o unittest5.ut -g  unittest5.c dominion.o rngs.o $(CFLAGS)
	./unittest1.ut >> unittestresults.out
	./unittest2.ut >> unittestresults.out
	./unittest3.ut >> unittestresults.out
	./unittest4.ut >> unittestresults.out
	./unittest5.ut >> unittestresults.out
	gcov -f -b dominion.c >> unittestresults.out
	# cat cardEffects.c.gcov

randomtestresults: clean randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o rngs.o
	gcc  -o randomtestcard1.rt -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard2.rt -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard3.rt -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1.rt >> randomtestresults.out
	./randomtestcard2.rt >> randomtestresults.out
	./randomtestcard3.rt >> randomtestresults.out
	gcov -f -b dominion.c >> randomtestresults.out