CC 	= gcc
CFLAGS 	= -Wall -Wextra -g
LDFLAGS = -lssl -lcrypto


all: blackjack init_money

blackjack: main.o term.o func.o saveload.o
	$(CC) $(CFLAGS) -o blackjack main.o term.o func.o saveload.o $(LDFLAGS)

init_money: init_money.o saveload.o
	$(CC) $(CFLAGS) -o init_money init_money.o saveload.o $(LDFLAGS)

init_money.o:
	$(CC) $(CFLAGS) -c init_money.c

main.o: main.c term_functions.h
	$(CC) $(CFLAGS) -c main.c

term.o: term_functions.c term_functions.h
	$(CC) $(CFLAGS) -c term_functions.c -o term.o

func.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c -o func.o

saveload.o: save_load.c save_load.h
	$(CC) $(CFLAGS) -c save_load.c -o saveload.o

clean:
	rm -f *.o blackjack init_money
cleano:
	rm -f *.o
