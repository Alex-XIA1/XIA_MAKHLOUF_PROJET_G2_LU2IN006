#include "Reseau.h"
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *tmp=R->noeuds;
    Noeud *res=NULL;
    while(tmp){
        if(tmp->nd->x==x && tmp->nd->y==y){ // Si on trouve le noeud correspondant
            res=tmp->nd;
            return res;
        }
        tmp=tmp->suiv;
    }
    // Noeud introuvable
    res=(Noeud *)malloc(sizeof(Noeud));
    if(res==NULL){
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }
    res->num=R->nbNoeuds+1;
    res->x=x;
    res->y=y;
    res->voisins=NULL;
    CellNoeud *newCell=(CellNoeud *)malloc(sizeof(CellNoeud));
    if(newCell==NULL){
        return NULL;
    }
    newCell->nd=res;
    newCell->suiv=R->noeuds;
    R->noeuds=newCell;
    R->nbNoeuds++;
    return res;
}
Reseau* reconstitueReseauListe(Chaines *C){
    CellChaine *tmp1=C->chaines;
    Reseau *res=(Reseau*)malloc(sizeof(Reseau));
    if(res==NULL){
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }
    res->gamma=C->gamma; // Nombre maximale de fibres inchangeable
    res->nbNoeuds=0; // Initialement le nombre de noeud est egale a 0
    Noeud *tmp2=rechercheCreeNoeudListe(res,tmp1->points->x,tmp1->points->y);
    res->commodites=(CellCommodite *)malloc(sizeof(CellCommodite));
    res->commodites->extrA=NULL;
    res->commodites->extrB=NULL;
    if(res->commodites==NULL){
         printf("Erreur d'allocation memoire\n");
         return NULL;
    }
    CellCommodite *tmp3=res->commodites;
    tmp1->points=tmp1->points->suiv;
    for( int i=0 ; i< C->nbChaines ; i++){
        tmp3->extrA=tmp2; // Premier point de la chaine est le premier point de la commodite
        while(tmp1->points){
            tmp2=rechercheCreeNoeudListe(res,tmp1->points->x,tmp1->points->y);
            if(tmp1->points->suiv==NULL){ // Si c'est le dernier point
                tmp3->extrB=tmp2; // On complete la commodite actuelle
            }
            tmp1->points=tmp1->points->suiv;
        }
        tmp1=tmp1->suiv;
        CellCommodite *tmp4=(CellCommodite *)malloc(sizeof(CellCommodite));
        if(tmp4==NULL){
            printf("Erreur d'allocation memoire\n");
            return NULL;
        }
        tmp4->extrA=NULL;
        tmp4->extrB=NULL;
        tmp3->suiv=tmp4;
        tmp3=tmp4;
    }
}
void liberer_noued(Noeud *nd){
    free(nd);
}
void liberer_liste_noeuds(CellNoeud *lNd){
    CellNoeud *tmp=NULL;
    while(lNd){
        tmp=lNd->suiv;
        liberer_noued(lNd->nd);
        free(lNd);
        lNd=tmp;
    }
}
void liberer_liste_commodites(CellCommodite *lc){
    CellCommodite *tmp=NULL;
    while(lc){
        tmp=lc->suiv;
        free(lc);
        lc=tmp;
    }
}
void liberer_reseau(Reseau *r){
    liberer_liste_noeuds(r->noeuds);
    liberer_liste_commodites(r->commodites);
    free(r);
}

//Exercice 6
Chaines* generationAleatoire(int nbChaines,int nbPointsChaine,int xmax, int ymax)