#include "ArbreQuat.h"
#include "Chaine.h"
#include "Reseau.h"

void chaineCoordMinMax(Chaines* C, double* xmin, double* ymin, double* xmax,double *ymax){
    Chaines* tmpC=C;
    if(tmpC==NULL){
        return;
    }
    
    CellChaine* tmpch=tmpC->chaines;
    if(tmpch==NULL){
        return;
    }
    //printf("Passee chaine\n");
    *xmin=tmpch->points->x;
    *xmax=tmpch->points->x;
    *ymin=tmpch->points->y;
    *ymax=tmpch->points->y;
    //printf("Passee chaine\n");
    CellPoint* tmpP=NULL;
    //printf("ALLO\n");

    while(tmpch!=NULL){
        tmpP=tmpch->points;
        while(tmpP!=NULL){
            if(tmpP->x<(*xmin)){
                //printf("ici les vals : tmpP->x = %lf et xmin= %lf\n",tmpP->x,*xmin);
                *xmin=(tmpP->x);
            }else if(tmpP->x>(*xmax)){
                //printf("ici l\n"); 
                *xmax=(tmpP->x);
            }
            if(tmpP->y<(*ymin)){
                *ymin=(tmpP->y);
            }else if(tmpP->y>(*ymax)){
                *ymax=(tmpP->y);
            }
            tmpP=tmpP->suiv;
            
        }
        //printf("chaque valeur est : xmax = %lf, xmin = %lf, ymax=%lf et ymin=%lf\n",*xmax,*xmin,*ymax,*ymin);
        tmpch=tmpch->suiv;
        
    }
    //printf("OK\n");
    //printf("au final chaque valeur est : xmax = %lf, xmin = %lf, ymax=%lf et ymin=%lf\n",*xmax,*xmin,*ymax,*ymin);
    //printf("OK\n");
}

ArbreQuat * creerArbreQuat(double xc, double yc, double coteX,double coteY){
    ArbreQuat* res=malloc(sizeof(ArbreQuat));
    res->xc=xc;
    res->yc=yc;
    res->coteX=coteX;
    res->coteY=coteY;
    res->noeud=NULL;
    res->so=NULL;
    res->se=NULL;
    res->no=NULL;
    res->ne=NULL;
    //printf("Passee l68\n");
    return res;
}

void insererNoeudArbre(Noeud * n,ArbreQuat** a, ArbreQuat* parent){
    if(n==NULL){
        return;
    }
    if(*a==NULL){
        //printf("Passee l76\n");
        double newcoteX=(parent->coteX)/2;
        double newcoteY=(parent->coteY)/2;
        double newxc;
        double newyc;
        //Dans l'ordre des tests so->se->no->ne
        //printf("Passee l82\n");
        if(n->x<parent->xc){
            newxc=(parent->xc)-(parent->coteX/4);
        }else{
            newxc=(parent->xc)+(parent->coteX/4);
        }
        if(n->y>parent->yc){
            newyc=(parent->yc)+((parent->coteY)/4);
        }else{
            newyc=(parent->yc)-((parent->coteY)/4);
        }
        //printf("ALLO ICI\n");
        
        /*if(n->x<parent->xc && n->y<parent->yc){
            newxc=parent->xc/2;
            newyc=parent->yc/2;
            //printf("Passee l87\n");
        }else if(n->x>=parent->xc && n->y<parent->yc){
            newxc=parent->xc+parent->xc/2;
            newyc=parent->yc/2;
            //printf("Passee l91\n");
        }else if(n->x<parent->xc && n->y>=parent->yc){
            newxc=parent->xc/2;
            newyc=parent->yc+parent->yc/2;
            //printf("Passee l95\n");
        }else if(n->x>=parent->xc && n->y>=parent->yc){
            newxc=parent->xc+parent->xc/2;
            newyc=parent->yc+parent->yc/2;
        }*/
        //printf("Passee l96_2\n");
        //On cree la nouvelle cellule
        parent=creerArbreQuat(newxc,newyc,newcoteX,newcoteY);
        //printf("Passee l99_2\n");
        parent->noeud=n;
        //printf("les vals parent->xc et yc = %lf et %lf\n",parent->xc,parent->yc);
        //printf("Passee l100\n");
        (*a)=parent;
        //printf("Passee l101\n");
        return;
    }else if((*a)->noeud!=NULL){
        //On oublie pas de mettre a jour parent
        parent=(*a);
        Noeud * ancienN=(*a)->noeud;
        (*a)->noeud=NULL;
        insererNoeudArbre(n,a,parent);
        parent=(*a);
        insererNoeudArbre(ancienN,a,parent);
        
        //Ceci ne marche pas et creer une boucle infinie
        //meme ordre que pour le cas vide so->se->no->ne
        /*if(n->x<(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(n,&((*a)->so),parent);
        }else if(n->x>=(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(n,&((*a)->se),parent);
        }else if(n->x<(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(n,&((*a)->no),parent);
        }else if(n->x>=(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(n,&((*a)->ne),parent);
        }
        printf("Passee l125 et parent->xc et yc= %lf, %lf\n",parent->xc,parent->yc);
        //On veut aussi inserer l'ancien noeud(attention : fait partie du bloc de la boucle infinie)
        
        parent=(*a);
        (*a)->noeud=NULL;
        if(n->x<(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(ancienN,&((*a)->so),parent);
        }else if(n->x>=(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(ancienN,&((*a)->se),parent);
        }else if(n->x<(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(ancienN,&((*a)->no),parent);
        }else if(n->x>=(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(ancienN,&((*a)->ne),parent);
        }*/
        //printf("On sort ?\n");
        //printf("Passee l127\n");


    }else if(*a!=NULL && ((*a)->noeud==NULL)){
        parent=(*a);
        //printf("Passee l144 et parent->xc et yc= %lf, %lf\n",parent->xc,parent->yc);
        if(n->x<(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(n,&((*a)->so),parent);
        }else if(n->x>=(*a)->xc && n->y<(*a)->yc){
            insererNoeudArbre(n,&((*a)->se),parent);
        }else if(n->x<(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(n,&((*a)->no),parent);
        }else if(n->x>=(*a)->xc && n->y>=(*a)->yc){
            insererNoeudArbre(n,&((*a)->ne),parent);
        }
        //printf("Passee l239\n");
    }
}

Noeud* rechercheCreeNoeudArbre(Reseau* R,ArbreQuat** a,ArbreQuat* parent,double x,double y){
    if(*a==NULL){
        //printf("Passee l139\n");
        Noeud *ajout=malloc(sizeof(Noeud));
        ajout->voisins=NULL;
        ajout->num=(++R->nbNoeuds);
        ajout->x=x;
        ajout->y=y;
        insererNoeudArbre(ajout,a,parent);
        CellNoeud* ajoutcell=malloc(sizeof(CellNoeud));
        ajoutcell->nd=ajout;
        if(R->noeuds!=NULL){
            ajoutcell->suiv=R->noeuds;
        }else{
            ajoutcell->suiv=NULL;
        }
        R->noeuds=ajoutcell;
        //printf("Passee l146\n");
        return ajout;
    
    }else if((*a)->noeud!=NULL){
        if((*a)->noeud->x==x && (*a)->noeud->y==y){
            //printf("Passee l149\n");
            return (*a)->noeud;
        }
        //printf("Passee l154\n");
        Noeud *ajout=malloc(sizeof(Noeud));
        ajout->voisins=NULL;
        ajout->num=(++R->nbNoeuds);
        ajout->x=x;
        ajout->y=y;
        parent=(*a);
        //printf("Passee l161\n");
        
        CellNoeud* ajoutcell=malloc(sizeof(CellNoeud));
        ajoutcell->nd=ajout;
        if(R->noeuds!=NULL){
            ajoutcell->suiv=R->noeuds;
        }else{
            ajoutcell->suiv=NULL;
        }
        R->noeuds=ajoutcell;
        //probleme ici
        //printf("Passee l197\n");
        insererNoeudArbre(ajout,a,parent);
        //printf("Passee l199\n");
        return ajout;
    }else if(*a!=NULL && ((*a)->noeud==NULL)){
        //printf("Passee l164\n");
        Noeud *ajout=NULL;
        if(x<(*a)->xc && y<(*a)->yc){
            ajout=rechercheCreeNoeudArbre(R,&((*a)->so),parent,x,y);
        }else if(x>=(*a)->xc && y<(*a)->yc){
            ajout=rechercheCreeNoeudArbre(R,&((*a)->se),parent,x,y);
        }else if(x<(*a)->xc && y>=(*a)->yc){
            ajout=rechercheCreeNoeudArbre(R,&((*a)->ne),parent,x,y);
        }else if(x>=(*a)->xc && y>=(*a)->yc){
            ajout=rechercheCreeNoeudArbre(R,&((*a)->no),parent,x,y);
        }else{
            //ne doit pas passer ici
            //printf("Que se passe t il\n");
            return ajout;
        }
        //printf("Passee l179\n");
        return ajout;
    }else{
        //printf("Que se passe t il 2\n");
        return NULL;
    }
}

Reseau* reconstitueReseauArbre(Chaines* C){
    Noeud *recup;
    Reseau *res=malloc(sizeof(Reseau));
    res->nbNoeuds=0;
    res->gamma=C->gamma;
    res->noeuds=NULL;
    res->commodites=NULL;

    double xmax,xmin,ymax,ymin;
    xmax=0;xmin=0;ymax=0;ymin=0;
    //printf("Passee\n");
    chaineCoordMinMax(C,&xmin,&ymin,&xmax,&ymax);
    //printf("Passee\n");
    //printf("Passee et valeur : %lf\n",xmin);
    //double coteX=sqrt(((xmax)-(xmin))*((xmax)-(xmin)));
    //double coteY=sqrt(((ymax)-(ymin))*((ymax)-(ymin)));
    /*double coteX=sqrt(((*xmax)-(*xmin))*((*xmax)-(*xmin)));
    double coteY=sqrt(((*ymax)-(*ymin))*((*ymax)-(*ymin)));*/
    ArbreQuat* abQ=creerArbreQuat(((xmax)+(xmin))/2,((ymax)+(ymin))/2,xmax-xmin,ymax-ymin);
    ArbreQuat* tmpab=abQ;
    ArbreQuat* parent=abQ;
    //printf("Passee\n");

    CellChaine *tmpC=C->chaines;
    while(tmpC){
        tmpab=abQ;
        parent=abQ;
        CellPoint *prec=tmpC->points;
        Noeud * ajoutp1=rechercheCreeNoeudArbre(res,&tmpab,parent,prec->x,prec->y);
        CellPoint *tmpP=NULL;
        Noeud * premiern=ajoutp1;
        //printf("Passee l211\n");
        if(prec!=NULL){
            //printf("Passee l213\n");
            tmpP=prec->suiv;
        }
        Noeud *derniern=NULL;
        //printf("Passee l217\n");
        while(tmpP!=NULL){
            //On ajoute le precedent aux voisins du noeud actuel
            //printf("Passee l220\n");
            recup=rechercheCreeNoeudArbre(res,&tmpab,parent,tmpP->x,tmpP->y);
            //printf("Passee l222\n");
            CellNoeud *vois=malloc(sizeof(CellNoeud));
            vois->nd=ajoutp1;
            vois->suiv=recup->voisins;
            recup->voisins=vois;
            //printf("Passee l225\n");
            //ON fait de meme pour le noeud precedent

            CellNoeud * tmp1=ajoutp1->voisins;
            int trouve=0;
            while(tmp1!=NULL){
                if(tmp1->nd==recup){
                    trouve=1;
                    break;
                }
                tmp1=tmp1->suiv;
                
            }
            //printf("Passee l238\n");

            if(trouve==0){
                CellNoeud *voisduprec=malloc(sizeof(CellNoeud));
                voisduprec->nd=recup;
                voisduprec->suiv=ajoutp1->voisins;
                ajoutp1->voisins=voisduprec;
                //printf("Passee l245\n");
            }
            //printf("Passee l247\n");

            ajoutp1=recup;
            if(tmpP->suiv==NULL){
                derniern=recup;
            }
            tmpP=tmpP->suiv;
        }

        if(premiern!=NULL && derniern!=NULL){
            CellCommodite* commo=malloc(sizeof(CellCommodite));
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
    //printf("Reseau construit avec succes !!!!\n");
    return res;
}

void detruire_arbre(ArbreQuat *a){
    if(a!=NULL){
        detruire_arbre(a->so);
        detruire_arbre(a->se);
        detruire_arbre(a->no);
        detruire_arbre(a->ne);
        liberer_noeud(a->noeud);
        free(a);
    }
}