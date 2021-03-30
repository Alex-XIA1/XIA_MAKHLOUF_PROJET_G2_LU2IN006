CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=ChaineMain

all: $(EXEC)

ChaineMain: Chaine.o ChaineMain.o SVGwriter.o
	$(CC) $(CFLAGS) -o ChaineMain Chaine.o SVGwriter.o ChaineMain.o -lm

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c Chaine.c -lm 

ChaineMain.o: ChaineMain.c SVGwriter.h Chaine.h
	$(CC) $(CFLAGS) -c ChaineMain.c -lm

SVGwrite.o: SVGwriter.c
	$(CC) $(CFLAGS) -c SVGwriter.c -lm
	
clean:
	rm -rf *.o ChaineMain
