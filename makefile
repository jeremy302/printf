
CC := gcc -Wall -Werror -Wextra #-pedantic -std=gnu89
TESTFILE := ./test

test: test.c *.o
	$(CC) *.o -o $(TESTFILE)
	$(TESTFILE)
test.c:
	echo "Skipping test.c"
*.o : *.c
	$(CC) -c *.c ./tests/*.c
./tests/*.o : ./tests/*.c
	$(CC) -c ./tests/*.c
retest:
	rm $(TESTFILE)
	make test

betty: *.c
	betty *.c
	echo betty

push: *.c
	git push origin main
	touch push
pull:
	git pull origin
