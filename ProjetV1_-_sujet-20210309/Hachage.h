#ifndef HACHAGE
#define HACHAGE
#include "Reseau.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct _TableHachage{
    int nbelem;
    int m;
    Noeud **T;
}TableHachage;

int foncK(double x, double y);
int foncH(int key, int m);
Noeud * rechercheCreeNoeudHachage (Reseau * R, TableHachage* H, double x, double y);
Reseau * reconstitueReseauHachage(Chaines *C, int M);


#endif