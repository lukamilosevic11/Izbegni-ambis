PROGRAM = izbegni_ambis
CC      = gcc
CFLAGS  = -Wall -std=c99
LDLIBS  = -lglut -lGLU -lGL -lm

$(PROGRAM): main.o svetlo.o objekti.o inicijalizacija.o rezultat.o
	$(CC) -o $(PROGRAM) $(LDLIBS) $^

main.o: main.c
	$(CC) $(CFLAGS) -c $^

svetlo.o: svetlo.c
	$(CC) $(CFLAGS) -c $(LDLIBS)  $^

rezultat.o: rezultat.c
	$(CC) $(CFLAGS) -c $(LDLIBS)  $^

objekti.o: objekti.c
	$(CC) $(CFLAGS) -c $(LDLIBS)  $^

inicijalizacija.o: inicijalizacija.c
	$(CC) $(CFLAGS) -c $(LDLIBS)  $^

.PHONY: clean

clean:
	-rm *.o $(PROGRAM)
