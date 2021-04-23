#include "Hachage.h"
#include "Reseau.h"
#include "SVGwriter.h"


//On utilise la formule de l'enonce
int foncK(double x, double y){
    return (int)(y+(x+y)*(x+y+1)/2);
}

//On utilise la formule de l'enonce (qui est la meme que celle du mini projet 2)
int foncH(int key, int M){
    int res=0;
    //On calcule A
    double A= (sqrt(5)-1)/2;
    //Pour obtenir les parties entieres on cast en int
    res= (int)(M*(key*A-(int)(key*A)));
    return res;
}

Noeud * rechercheCreeNoeudHachage(Reseau *R, TableHachage *H,double x, double y){
    int clefH=foncH(foncK(x,y),H->m);
    if(H->T[clefH]!=NULL){
        CellNoeud* tmp=H->T[clefH];
        while(tmp!=NULL){
            if(tmp->nd->x==x && tmp->nd->y==y){
                return tmp->nd;
            }
            tmp=tmp->suiv;
        }
        Noeud * ajout=malloc(sizeof(Noeud));
        //On peut passer par la table de hachage pour definir le numero
        //ajout->num=(++H->nbelem);
        ajout->num=(++R->nbNoeuds);
        ajout->x=x;
        ajout->y=y;
        ajout->voisins=NULL;
        CellNoeud* ajoutcell=malloc(sizeof(CellNoeud));
        ajoutcell->nd=ajout;
        if(R->noeuds!=NULL){
            ajoutcell->suiv=R->noeuds;
        }else{
            ajoutcell->suiv=NULL;
        }
        R->noeuds=ajoutcell;

        ajoutcell->suiv=H->T[clefH];
        H->T[clefH]=ajoutcell;
        return ajout;
    }else{
        Noeud * ajout=malloc(sizeof(Noeud));
        //ajout->num=(++H->nbelem);
        ajout->num=(++R->nbNoeuds);
        ajout->x=x;
        ajout->y=y;
        ajout->voisins=NULL;
        CellNoeud* ajoutcell=malloc(sizeof(CellNoeud));
        ajoutcell->nd=ajout;
        if(R->noeuds!=NULL){
            ajoutcell->suiv=R->noeuds;
           
        }else{
            ajoutcell->suiv=NULL;
            
        }
        R->noeuds=ajoutcell;

        H->T[clefH]=ajoutcell;
        return ajout;
    }
}

Reseau* reconstitueReseauHachage(Chaines *C, int M){
    Reseau * res=malloc(sizeof(Reseau));
    res->nbNoeuds=0;
    res->gamma=C->gamma;
    res->noeuds=NULL;
    res->commodites=NULL;
    TableHachage* tabH=malloc(sizeof(TableHachage));
    tabH->nbelem=0;
    tabH->m=M;
    tabH->T=malloc(M*sizeof(CellNoeud*));
    for(int i=0;i<tabH->m;i++){
        tabH->T[i]=NULL;
    }
    CellChaine *tmpC=C->chaines;
    while(tmpC){
        CellPoint *prec=tmpC->points;
        Noeud * ajoutp1=rechercheCreeNoeudHachage(res,tabH,prec->x,prec->y);
        CellPoint *tmpP=NULL;
        Noeud * premiern=ajoutp1;
        if(prec!=NULL){
            tmpP=prec->suiv;
        }
        Noeud *derniern=NULL;
        while(tmpP!=NULL){
            Noeud * recup=rechercheCreeNoeudHachage(res,tabH,tmpP->x,tmpP->y);
            CellNoeud *vois=malloc(sizeof(CellNoeud));
            vois->nd=ajoutp1;
            vois->suiv=recup->voisins;
            recup->voisins=vois;
            

            //On ajoute le noeud actuel au voisins du precedent
            //On veut eviter les doublons on parcourt donc la liste des voisins du precedent
            //on parcours les voisins de ajoutp1
            CellNoeud *tmp1=ajoutp1->voisins;
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
                voisduprec->suiv=ajoutp1->voisins;
                ajoutp1->voisins=voisduprec;
            }

            ajoutp1=recup;
            if(tmpP->suiv==NULL){
                derniern=recup;
            }
            tmpP=tmpP->suiv;
        }

        //Recupere les noeuds
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

void afficheReseauHSVG(Reseau *R, char* nomInstance){
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

//A verifier
void detruireTableH(TableHachage* cible){
    CellNoeud* tmp;
    for(int i = 0;i<cible->m;i++){
        while(cible->T[i]!=NULL){
            tmp=cible->T[i];
            cible->T[i]=cible->T[i]->suiv;
            //Utilise la fonction de liberation d'un cellnoeud
            liberer_liste_noeuds(tmp);
            //liberer les voisins aussi ou pas
        }
    }
    //On oublie pas de liberer le tableau et la structure
    free(cible->T);
    free(cible);
}