#ifndef HACHAGE
#define HACHAGE
#include "Reseau.h"
#include "SVGwriter.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct _TableHachage{
    int nbelem;
    int m;
    CellNoeud **T;
}TableHachage;

int foncK(double x, double y);
int foncH(int key, int m);
Noeud * rechercheCreeNoeudHachage (Reseau * R, TableHachage* H, double x, double y);
Reseau * reconstitueReseauHachage(Chaines *C, int M);
void afficheReseauHSVG(Reseau *R, char* nomInstance);

#endif