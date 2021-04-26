#include "Reseau.h"
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *tmp=R->noeuds;
    Noeud *res=NULL;
    while(tmp!=NULL){
        printf("r_x: %f\n",tmp->nd->x);
        printf("r_y: %f\n",tmp->nd->y);
        printf("x=%f : y=%f\n",x,y);
        printf("------------------\n");
        //printf("x_suiv :%f , y_suiv :%f\n",tmp->suiv->nd->x,tmp->suiv->nd->y);
        if(tmp->nd->x==x && tmp->nd->y==y){ // Si on trouve le noeud correspondant
            printf("Passe\n");
            res=tmp->nd;
            printf("%f : %f\n",res->x,res->y);
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
    CellPoint *tmp3=NULL;
    while(tmp1){ // Parcours de la liste des chaines
        printf("debut\n");
        CellPoint *tmp2=tmp1->points; // Liste des points de chaque chaine
        n=rechercheCreeNoeudListe(res,tmp2->x,tmp2->y);
        c=(CellCommodite *)malloc(sizeof(CellCommodite));
        if(c==NULL){
            printf("Erreur d'allocation memoire\n");
            return NULL;
        }
        c->extrA=n;
        while(tmp2->suiv){ // Parcours de la liste des points
            CellPoint *p_suiv=tmp2->suiv;
            Noeud *n_suiv=rechercheCreeNoeudListe(res,p_suiv->x,p_suiv->y);
            //Maj voisinage
            CellNoeud *n_voisins=n->voisins;
            while(n_voisins!=NULL && n_voisins->nd->num!=n_suiv->num){
                n_voisins=n_voisins->suiv;
            }
            if(n_voisins==NULL){
                CellNoeud *v=(CellNoeud *)malloc(sizeof(CellNoeud));
                if(v==NULL){
                    printf("Erreur d'allocation memoire\n");
                    return NULL;
                }
                v->nd=n_suiv;
                v->suiv=n->voisins;
                n->voisins=v;
                
            }
            // Maj voisinage
            CellNoeud *suiv_voisins=n_suiv->voisins;
            while(suiv_voisins!=NULL && suiv_voisins->nd->num!=n->num){
                suiv_voisins=suiv_voisins->suiv;
            }
            if(suiv_voisins==NULL){
                CellNoeud *suiv_v=(CellNoeud *)malloc(sizeof(CellNoeud));
                if(suiv_v==NULL){
                    printf("Erreur d'allocation memoire\n");
                    return NULL;
                }
                suiv_v->nd=n;
                suiv_v->suiv=n_suiv->voisins;
                n_suiv->voisins=suiv_v;
            }
            tmp3=tmp2;
            tmp2=tmp2->suiv;
        }
        c->extrB=rechercheCreeNoeudListe(res,tmp3->x,tmp3->y);
        c=c->suiv;
        tmp1=tmp1->suiv;
    }
    return res;
}

void liberer_noued(Noeud *nd){
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
void liberer_noeud(Noeud *nd){  
    CellNoeud *cellcourant;
    while (nd->voisins){
        cellcourant = nd->voisins;
        nd->voisins = nd->voisins->suiv;
        free(cellcourant);
    }
    free(nd);
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

int nbCommodites(Reseau *R){
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
/*void afficheReseauSVG(Reseau *R, char* nomInstance){
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