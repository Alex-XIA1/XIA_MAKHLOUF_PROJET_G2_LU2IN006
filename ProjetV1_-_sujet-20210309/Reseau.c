#include "Reseau.h"
#include "Chaine.h"
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *tmp=R->noeuds;
    Noeud *res=NULL;
    while(tmp!=NULL){
        //printf("je suis ici\n");
        //printf("x_suiv :%f , y_suiv :%f\n",tmp->suiv->nd->x,tmp->suiv->nd->y);
        if(tmp->nd->x==x && tmp->nd->y==y){ // Si on trouve le noeud correspondant
            printf("Passe\n");
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
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }
    newCell->nd=res;
    newCell->suiv=R->noeuds;
    R->noeuds=newCell;
    R->nbNoeuds++;
    return res;
}
/*Reseau* reconstitueReseauListe(Chaines *C){
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
}*/
void ajouteVoisinDebut(Noeud *n, CellNoeud *v){
    if(n->voisins==NULL){
        n->voisins=v;
    }else{
        v->suiv=n->voisins;
        n->voisins=v;
    }
}
Reseau* reconstitueReseauListe(Chaines *C){
    Reseau * res=(Reseau *)malloc(sizeof(Reseau));
    if(res==NULL){
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }
    res->gamma=C->gamma; // Nombre maximum de fibres par cable
    res->nbNoeuds=0; // Nombre de noeuds du reseau est initialement null
    res->noeuds=NULL;
    res->commodites=NULL;
    CellChaine * tmp1=C->chaines; // Liste chainee des chaines
    int cpt=0;
    CellCommodite *c=res->commodites;
    Noeud *n=NULL;
    while(tmp1){
        printf("debut\n");
        CellPoint *tmp2=tmp1->points; // Liste des points de chaque chaine
        CellPoint *tmp3=NULL;
        CellNoeud *prec=NULL;
        //printf("passe1\n");
        n=rechercheCreeNoeudListe(res,tmp2->x,tmp2->y);
        printf("passe recherche\n");
        prec=res->noeuds;
        c=(CellCommodite *)malloc(sizeof(CellCommodite));
            if(c==NULL){
                printf("Erreur d'allocation\n");
                return NULL;
            }
        c->extrA=n;
        tmp2=tmp2->suiv;
        while(tmp2){
            //printf("it: %d\n",cpt);
            printf("debut r2\n");
            n=rechercheCreeNoeudListe(res,tmp2->x,tmp2->y);
            printf("fin r2\n");
            ajouteVoisinDebut(n,prec);
            ajouteVoisinDebut(prec->nd,res->noeuds);
            prec=res->noeuds;
            tmp3=tmp2;
            tmp2=tmp2->suiv;
            //printf("fin it: %d\n",cpt);
        }
        c->extrB=rechercheCreeNoeudListe(res,tmp3->x,tmp3->y);
        cpt++;
        tmp1=tmp1->suiv;
        c=c->suiv;
        printf("fin\n");
    }
    return res;
}

void liberer_noeud(Noeud *nd){
    if(nd){
        CellNoeud *tmp=nd->voisins;
        CellNoeud *tmp2=NULL;
        while(tmp){
            tmp2=tmp->suiv;
            free(tmp);
            tmp=tmp2;
        }
        free(nd);
    }
}
void liberer_liste_noeuds(CellNoeud *lNd){
    CellNoeud *tmp=NULL;
    while(lNd){
        tmp=lNd->suiv;
        liberer_noeud(lNd->nd);
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

/*int nbCommodites(Reseau *R){
    int cpt=0;
    CellCommodite *c=R->commodites;
    while(c){
        cpt++;
        c=c->suiv;
    }
    return cpt;
}
int nbLiaisons(Reseau *R){
    CellNoeud *listeN1=R->noeuds;
    int *tab=malloc(sizeof(int)*500);
    int index=0;
    int cpt=0;
    int bool=0;
    while(listeN1){
        Noeud *n=listeN1->nd;
        CellNoeud *v=n->voisins;
        while(v){
            for(int i=0;i<500;i++){
                if(tab[i]==v->nd->num)
                    bool=1;

            }
            if(bool==0 ){
                if(index<500){
                    cpt++;
                    tab[index]=v->nd->num;
                    index++;
                }else{
                    printf("Tableau plein!!");
                }
            }
            bool=0;
            v=v->suiv;

        }
        listeN1=listeN1->suiv;
    }
    free(tab);
    return cpt;
}
void ecrireReseau(Reseau *R, FILE *f){
    if(f!=NULL){
        fprintf(f,"NbNoeuds: %d\n",R->nbNoeuds);
        fprintf(f,"NbLiaisons: %d\n",nbLiaisons(R));
        fprintf(f,"NbCommodites: %d\n\n\n",nbCommodites(R));
        CellNoeud *noeuds=R->noeuds;
        while(noeuds){
            fprintf(f,"v %d %f %f\n",noeuds->nd->num,noeuds->nd->x,noeuds->nd->y);
            noeuds=noeuds->suiv;
        }
        int *tab=malloc(sizeof(int)*500);
        int bool=0;
        noeuds=R->noeuds;
        while(noeuds){
            for(int i=0;i<500;i++){
                if(tab[i]==noeuds->nd->num)
                    bool=1;
            }
            if(bool==0){
                CellNoeud *v=noeuds->nd->voisins;
                while(v){
                    fprintf(f,"l %d %d\n",noeuds->nd->num,v->nd->num);
                    v=v->suiv;
                }
            }
            bool=0;
            noeuds=noeuds->suiv;
        }
        CellCommodite *commodites=R->commodites;
        while(commodites){
            fprintf(f,"k %d %d",commodites->extrA->num,commodites->extrB->num);
            commodites=commodites->suiv;
        }
        fclose(f);
    }else{
        printf("Fichier passe en parametre non ouvert");
    }
}
void afficheReseauSVG(Reseau *R, char* nomInstance){
    CellNoeud *courN,*courv;
    SVGwriter svg;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;

    courN=R->noeuds;
    while (courN!=NULL){
        if (maxx<courN->nd->x) maxx=courN->nd->x;
        if (maxy<courN->nd->y) maxy=courN->nd->y;
        if (minx>courN->nd->x) minx=courN->nd->x;
        if (miny>courN->nd->y) miny=courN->nd->y;
        courN=courN->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    courN=R->noeuds;
    while (courN!=NULL){
        SVGpoint(&svg,500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
        courv=courN->nd->voisins;
        while (courv!=NULL){
            if (courv->nd->num<courN->nd->num)
                SVGline(&svg,500*(courv->nd->x-minx)/(maxx-minx),500*(courv->nd->y-miny)/(maxy-miny),500*(courN->nd->x-minx)/(maxx-minx),500*(courN->nd->y-miny)/(maxy-miny));
            courv=courv->suiv;
        }
        courN=courN->suiv;
    }
    SVGfinalize(&svg);
}*/
