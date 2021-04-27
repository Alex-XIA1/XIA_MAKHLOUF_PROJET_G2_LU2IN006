CC=gcc
CFLAGS=-W -Wall -pedantic
EXEC=ChaineMain HachageMain ReconstitueReseau

all: $(EXEC)

ChaineMain: Chaine.o ChaineMain.o SVGwriter.o Hachage.o ArbreQuat.o Reseau.o
	$(CC) $(CFLAGS) -o ChaineMain Chaine.o SVGwriter.o ChaineMain.o Hachage.o ArbreQuat.o Reseau.o -lm

Chaine.o: Chaine.c
	$(CC) $(CFLAGS) -c Chaine.c -lm 

ChaineMain.o: ChaineMain.c SVGwriter.h Chaine.h Hachage.h ArbreQuat.h Reseau.h 
	$(CC) $(CFLAGS) -c ChaineMain.c -lm

SVGwriter.o: SVGwriter.c
	$(CC) $(CFLAGS) -c SVGwriter.c -lm

HachageMain: Hachage.o HachageMain.o SVGwriter.o Reseau.o
	$(CC) $(CFLAGS) -o HachageMain Hachage.o HachageMain.o SVGwriter.o Reseau.o

Hachage.o: Hachage.c
	$(CC) $(CFLAGS) -c Hachage.c -lm

HachageMain.o : HachageMain.c Hachage.h Reseau.h
	$(CC) $(CFLAGS) -c HachageMain.c -lm

Reseau.o: Reseau.c Reseau.h SVGwriter.h
	$(CC) $(CFLAGS) -c Reseau.c -lm

ReconstitueReseau: ReconstitueReseau.o Reseau.o Chaine.o SVGwriter.o
	$(CC) $(CFLAGS) -o ReconstitueReseau ReconstitueReseau.o Reseau.o Chaine.o SVGwriter.o -lm 

ReconstitueReseau.o: ReconstitueReseau.c Reseau.h Chaine.h 
	$(CC) $(CFLAGS) -c ReconstitueReseau.c -lm
ArbreQuat.o:ArbreQuat.c
	$(CC) $(CFLAGS) -c ArbreQuat.c -lm

clean:
	rm -rf *.o ChaineMain HachageMain ReconstitueReseau
