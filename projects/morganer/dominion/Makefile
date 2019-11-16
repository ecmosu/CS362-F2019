CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

cardEffects.o: cardEffects.h cardEffects.c
	gcc -c cardEffects.c -g  $(CFLAGS)

dominion_helpers.o: dominion_helpers.h dominion_helpers.c
	gcc -c dominion_helpers.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o cardEffects.o dominion_helpers.o
	gcc -c dominion.c -g $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g cardEffects.o dominion_helpers.o dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


randomtestresults: clean randomtestcard1.c randomtestcard2.c randomtestcard3.c dominion.o dominion_helpers.o rngs.o
	gcc  -o randomtestcard1.rt -g  randomtestcard1.c cardEffects.o dominion_helpers.o dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard2.rt -g  randomtestcard2.c cardEffects.o dominion_helpers.o dominion.o rngs.o $(CFLAGS)
	gcc  -o randomtestcard3.rt -g  randomtestcard3.c cardEffects.o dominion_helpers.o dominion.o rngs.o $(CFLAGS)
	./randomtestcard1.rt
	./randomtestcard2.rt
	./randomtestcard3.rt
	gcov -f -b cardEffects.c
	# ./randomtestcard1.ut >> randomtestresults.out
	# gcov -f -b cardEffects.c >> randomtestresults.out
	# cat cardEffects.c.gcov

player: player.c interface.o
	gcc -o player player.c -g cardEffects.o dominion_helpers.o dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe *.ut  *.rt *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
