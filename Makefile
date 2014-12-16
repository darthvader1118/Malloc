CC=gcc
CFLAGS = -Wall -g -O

custom:
	$(CC) $(CFLAGS) main.c myMalloc.c -o custom
run: custom
	./custom
clean:
	rm *.o custom
