#include "Reseau.h"
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *tmp=R->noeuds;
    while(tmp){
        if ( tmp->nd->x==x && tmp->nd->x==y ){
            return tmp->nd;
        }
        tmp=tmp->suiv;
    }
    Noeud *newN=(Noeud *)malloc(sizeof(Noeud));
    if(newN==NULL){
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }
    newN->num=R->nbNoeuds+1;
    R->nbNoeuds++;
    newN->x=x;
    newN->y=y;
    newN->voisins=NULL;
    tmp->suiv=newN;
    return newN;
}
