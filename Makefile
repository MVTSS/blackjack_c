CC 	= gcc
CFLAGS 	= -Wall -Wextra -g
LDFLAGS = -lssl -lcrypto -lcjson


all: blackjack init_money

blackjack: main.o term.o func.o saveload.o deck.o player.o language.o config.o json_manip.o
	$(CC) $(CFLAGS) -o blackjack main.o term.o func.o saveload.o deck.o player.o language.o config.o json_manip.o $(LDFLAGS)

init_money: init_money.o saveload.o
	$(CC) $(CFLAGS) -o init_money init_money.o saveload.o $(LDFLAGS)

init_money.o:
	$(CC) $(CFLAGS) -c init_money.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

json_manip.o: json_manipulation.c json_manipulation.h
	$(CC) $(CFLAGS) -c json_manipulation.c -o json_manip.o

main.o: main.c term_functions.h
	$(CC) $(CFLAGS) -c main.c

term.o: term_functions.c term_functions.h
	$(CC) $(CFLAGS) -c term_functions.c -o term.o

func.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c -o func.o

deck.o: deck.c deck.h
	$(CC) $(CFLAGS) -c deck.c -o deck.o

player.o: player.c player.h
	$(CC) $(CFLAGS) -c player.c -o player.o

language.o: language.c language.h
	$(CC) $(CFLAGS) -c language.c -o language.o

saveload.o: save_load.c save_load.h
	$(CC) $(CFLAGS) -c save_load.c -o saveload.o

clean:
	rm -f *.o blackjack init_money
cleano:
	rm -f *.o
