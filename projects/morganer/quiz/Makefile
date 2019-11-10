CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: clean testme.c
	gcc -o testme.a testme.c -g $(CFLAGS)
	./testme.a

clean:
	rm -f testme.a *.gcov *.gcda *.gcno