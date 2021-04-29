#ifndef __GRAPHE_H__
#define __GRAPHE_H__
#include<stdlib.h>
#include<stdio.h>
#include "Struct_Liste.h"
#include "Struct_File.h"
#include "Reseau.h"

typedef struct{
  int u,v;        /* Numeros des sommets extremité */
} Arete;


typedef struct cellule_arete{
  Arete *a;     /* pointeur sur l'arete */
  struct cellule_arete *suiv;
} Cellule_arete;


typedef struct {
  int num;                 /* Numero du sommet (le meme que dans T_som) */
  double x, y;
  Cellule_arete* L_voisin;  /* Liste chainee des voisins */
} Sommet;


typedef struct{
  int e1,e2;    /* Les deux extremites de la commodite */
} Commod;


typedef struct{
  int nbsom;        /* Nombre de sommets */
  Sommet **T_som;    /* Tableau de pointeurs sur sommets */
  int gamma;     
  int nbcommod;     /* Nombre de commodites */
  Commod *T_commod; /* Tableau des commodites */
} Graphe;
void *afficheErreur();
Graphe *creerGraphe(Reseau *r);
int plus_petit_nombre_aretes(Graphe *g, int u,int v);
int* pere(Graphe* g, int u, int s);
ListeEntier chemin(Graphe* g, int r, int s);
void liberer_arete(Cellule_arete *CA);
void liberer_sommets(Sommet **T_som, int nbsom);
void liberer_graphe(Graphe *g);
int reorganiseReseau(Reseau* r);
#endif
