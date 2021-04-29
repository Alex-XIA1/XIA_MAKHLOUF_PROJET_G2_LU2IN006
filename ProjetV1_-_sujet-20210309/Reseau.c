#include "Reseau.h"
#include "SVGwriter.h"

// 2.1 Fonction de recherche(ou creation) d'un noeud dans un reseau
Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
    CellNoeud *tmp=R->noeuds;
    Noeud *res=NULL;
    while(tmp!=NULL){
        //printf("x_suiv :%f , y_suiv :%f\n",tmp->suiv->nd->x,tmp->suiv->nd->y);
        if(tmp->nd->x==x && tmp->nd->y==y){ // Si on trouve le noeud correspondant
            //printf("Passe\n");
            res=tmp->nd;
            //printf("%f : %f\n",res->x,res->y);
            return res;
        }
        tmp=tmp->suiv;
    }
    // Noeud introuvable
    // Creation du noeud 
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


// 2.2 Fonction de reconstitution d'un reseau a prtir d'une liste de chaines
Reseau* reconstitueReseauListe(Chaines *C){
    // Creation du reseau
    Reseau * res=(Reseau *)malloc(sizeof(Reseau));
    
    if(res==NULL){
        printf("Erreur d'allocation memoire\n");
        return NULL;
    }

    // Initialisation des diferents champs

    res->gamma=C->gamma; // Nombre maximum de fibres par cable
    res->nbNoeuds=0; // Nombre de noeuds du reseau est initialement null
    res->noeuds=NULL;
    res->commodites=NULL;
    CellChaine * tmpC=C->chaines; // Liste chainee des chaines
    while(tmpC){ // Parcours de la liste des chaines
        CellPoint *prec=tmpC->points;
        Noeud * n=rechercheCreeNoeudListe(res,prec->x,prec->y);
        CellPoint *tmpP=NULL;
        Noeud * premiern=n;
        if(prec!=NULL){
            tmpP=prec->suiv;
        }
        Noeud *derniern=NULL;
        while(tmpP!=NULL){
            Noeud * recup=rechercheCreeNoeudListe(res,tmpP->x,tmpP->y);
            CellNoeud *vois=malloc(sizeof(CellNoeud));
            vois->nd=n;
            vois->suiv=recup->voisins;
            recup->voisins=vois;
            

            //On ajoute le noeud actuel au voisins du precedent
            //On veut eviter les doublons on parcourt donc la liste des voisins du precedent
            //on parcours les voisins de n
            CellNoeud *tmp1=n->voisins;
            int trouve=0;
            while(tmp1!=NULL){
                if(tmp1->nd==recup){
                    //printf("JE PASSE ICI\n");
                    trouve=1;
                    break;
                }
                tmp1=tmp1->suiv;
            }
            if(trouve==0){
                CellNoeud *voisduprec=malloc(sizeof(CellNoeud));
                voisduprec->nd=recup;
                voisduprec->suiv=n->voisins;
                n->voisins=voisduprec;
            }

            n=recup;
            if(tmpP->suiv==NULL){
                derniern=recup;
            }

            
            tmpP=tmpP->suiv;
        }
        if(premiern!=NULL && derniern!=NULL){
            CellCommodite* commo= malloc(sizeof(CellCommodite));
            commo->extrA=premiern;
            commo->extrB=derniern;
            if(res->commodites==NULL){
                commo->suiv=NULL;
            }else{
                commo->suiv=res->commodites;
            }
            res->commodites=commo;
        }
        tmpC=tmpC->suiv;
    }
    return res;
}

// 3.1

// Fonction de calcul du nombre de commodites dans un reseau
int nbCommodites(Reseau *R){
    int cpt=0;
    CellCommodite *c=R->commodites;
    while(c){
        cpt++;
        c=c->suiv;
    }
    return cpt;
}

// Fonction de calcul du nombre de liaisons dans un reseau
int nbLiaisons(Reseau *R){
    liste_L *l=NULL;
    int cpt=0;
    CellNoeud *noeuds=R->noeuds;
    while(noeuds){
        CellNoeud *voisins=noeuds->nd->voisins;
        while(voisins){
            int trouve=0;
            liste_L *tmp=l;
            while(tmp){
                if((tmp->tab[0]==noeuds->nd->num && tmp->tab[1]==voisins->nd->num) ||
                   (tmp->tab[0]==voisins->nd->num && tmp->tab[1]==noeuds->nd->num)){
                       trouve=1;
                   }
                tmp=tmp->suiv;
            }
            if(trouve==0){

                liste_L *newCell=(liste_L *)malloc(sizeof(liste_L));
                newCell->tab=(int *)malloc(sizeof(int)*2);
                newCell->suiv=NULL;
                newCell->tab[0]=noeuds->nd->num;
                newCell->tab[1]=voisins->nd->num;
                newCell->suiv=l;
                l=newCell;
                cpt++;
            }
            voisins=voisins->suiv;
        }
        noeuds=noeuds->suiv;
    }
    while(l){
        liste_L *tmp=l->suiv;
        free(l->tab);
        free(l);
        l=tmp;
    }
    return cpt;
}

// 3.2 Fonction d'ecriture d'un reseau

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
        liste_L *l=NULL;
        noeuds=R->noeuds;
        while(noeuds){
            CellNoeud *voisins=noeuds->nd->voisins;
            while(voisins){
                int trouve=0;
                liste_L *tmp=l;
                while(tmp){
                    if((tmp->tab[0]==noeuds->nd->num && tmp->tab[1]==voisins->nd->num) ||
                       (tmp->tab[0]==voisins->nd->num && tmp->tab[1]==noeuds->nd->num)){
                           trouve=1;
                       }
                    tmp=tmp->suiv;
                }
                if(trouve==0){
                    liste_L *newCell=(liste_L *)malloc(sizeof(liste_L));
                    newCell->tab=(int *)malloc(sizeof(int)*2);
                    newCell->suiv=NULL;
                    newCell->tab[0]=noeuds->nd->num;
                    newCell->tab[1]=voisins->nd->num;
                    newCell->suiv=l;
                    l=newCell;
                    fprintf(f,"l %d %d\n",l->tab[0],l->tab[1]);
                }
                voisins=voisins->suiv;
            }
            noeuds=noeuds->suiv;
        }
        while(l){
            liste_L *tmp=l->suiv;
            free(l->tab);
            free(l);
            l=tmp;
        }
        CellCommodite *commodites=R->commodites;
        while(commodites){
            fprintf(f,"k %d %d\n",commodites->extrA->num,commodites->extrB->num);
            commodites=commodites->suiv;
        }
        fclose(f);
    }else{
        printf("Fichier passe en parametre non ouvert");
    }
}

// 3.3 Fonction d'affichage d'un reseau
void afficheReseauSVGL2(Reseau *R, char* nomInstance){
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
}
// Fonctions de desalocation memoire
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