CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=ChaineMain HachageMain

all: $(EXEC)

ChaineMain: Chaine.o ChaineMain.o SVGwriter.o Hachage.o ArbreQuat.o
	$(CC) $(CFLAGS) -o ChaineMain Chaine.o SVGwriter.o ChaineMain.o Hachage.o ArbreQuat.o -lm

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c Chaine.c -lm 

ChaineMain.o: ChaineMain.c SVGwriter.h Chaine.h Hachage.h ArbreQuat.h
	$(CC) $(CFLAGS) -c ChaineMain.c -lm

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c SVGwriter.c -lm

HachageMain: Hachage.o HachageMain.o SVGwriter.o
	$(CC) $(CFLAGS) -o HachageMain Hachage.o HachageMain.o SVGwriter.o

Hachage.o: Hachage.c
	$(CC) $(CFLAGS) -c Hachage.c -lm

HachageMain.o : HachageMain.c Hachage.h Reseau.h
	$(CC) $(CFLAGS) -c HachageMain.c -lm

ArbreQuat.o:ArbreQuat.c
	$(CC) $(CFLAGS) -c ArbreQuat.c -lm

clean:
	rm -rf *.o ChaineMain HachageMain
