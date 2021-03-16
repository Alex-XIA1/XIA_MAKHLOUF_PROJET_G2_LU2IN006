CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=ChaineMain

all: $(EXEC)

ChaineMain: Chaine.o ChaineMain.o
	$(CC) $(CFLAGS) -o ChaineMain Chaine.o ChaineMain.o

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c Chaine.c

ChaineMain.o: ChaineMain.c
	$(CC) $(CFLAGS) -c ChaineMain.c
	
clean:
	rm -rf *.o ChaineMain
