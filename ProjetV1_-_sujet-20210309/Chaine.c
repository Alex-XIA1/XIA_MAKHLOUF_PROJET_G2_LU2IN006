#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <math.h>
#include "Chaine.h"
#include "SVGwriter.h"

Chaines * lectureChaines(FILE* f){
    FILE* ptr =NULL;
    ptr = f;
    if(ptr==NULL){
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    Chaines *res =malloc(sizeof(Chaines));
    res->gamma=0;
    res->nbChaines=0;
    res->chaines=NULL;

    char buffer[256];
    int num=0;
    int nbCh=0;
    float x;
    float y;

    fscanf(ptr,"%s %d",buffer,&res->gamma);
    //printf("gamma = %d\n",res->gamma);
    /*fgets(buffer,256,ptr);
    buffer[strlen(buffer)-1]='\0';*/
    fscanf(ptr,"%s %d",buffer,&res->nbChaines);
    //printf("chaines %d\n",res->nbChaines);
    /*if(fgets(buffer,256,ptr)==NULL){
        return;
    }*/
    

    while(fscanf(ptr,"%d %d",&num,&nbCh)!=EOF){
        //printf("num = %d\n",num);
        //printf("nbCh = %d\n",nbCh);
        //sleep(1);
        int tpint = nbCh;
        //printf("values num = %d\n",num);
        CellChaine *tmp=malloc(sizeof(CellChaine));
            if(res->chaines==NULL){
                tmp->suiv=NULL;
                res->chaines=tmp;
            }else{
                tmp->suiv=res->chaines;
                res->chaines=tmp;
            }
            tmp->numero=num;
            tmp->points=NULL;
        while(tpint>0){
            //printf("ICI\n");
            if(fscanf(ptr,"%f %f",&x,&y)){
                CellPoint *tmp2=malloc(sizeof(CellPoint));
                if(tmp->points==NULL){
                    tmp2->suiv=NULL;
                    tmp->points=tmp2;
                }else{
                    tmp2->suiv=tmp->points;
                    tmp->points=tmp2;
                }
                tmp2->x=x;
                tmp2->y=y;
                //printf("Valeurs x = %.2f, y = %.2f\n",x,y);
            }else{
                printf("KO/FIN ?\n");
            }
            tpint--;
            //printf("tpint = %d\n",tpint);
        }
    }
    
    return res;

}


void ecrireChaines(Chaines *C, FILE *f){
    FILE *ptr =NULL;
    ptr = f;
    Chaines* tmp = C;

    if(tmp==NULL){
        return;
    }

    fprintf(ptr,"NbChain: %d\n",tmp->nbChaines);
    fprintf(ptr,"gamma: %d\n", tmp->gamma);
    fprintf(ptr,"\n");
    
    CellChaine* tmp2=tmp->chaines;
    
    if(tmp2==NULL){
        return;
    }
    
    while(tmp2){
        int cpt=0;
        int num = tmp2->numero;

        CellPoint* ctmp=tmp2->points;
        while(ctmp){
            ctmp=ctmp->suiv;
            cpt++;
        }
        //printf("la valeur de ctmp = %d pour num = %d\n",cpt,num);
        fprintf(ptr,"%d %d ",num,cpt);

        CellPoint* ptmp=tmp2->points;
        while(ptmp){
            double x=ptmp->x;
            double y=ptmp->y;
            fprintf(ptr,"%.2lf %.2lf ",x,y);
            ptmp=ptmp->suiv;
            //printf("valeurs pour x : %.2f et y : %.2f\n",x,y);
        }
        tmp2=tmp2->suiv;
        //printf("ICI\n");
        fprintf(ptr,"\n");
    }

}

void afficheChainesSVG(Chaines *C, char* nomInstance){
    //int i;
    double maxx=0,maxy=0,minx=1e6,miny=1e6;
    CellChaine *ccour;
    CellPoint *pcour;
    double precx,precy;
    SVGwriter svg;
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        while (pcour!=NULL){
            if (maxx<pcour->x) maxx=pcour->x;
            if (maxy<pcour->y) maxy=pcour->y;
            if (minx>pcour->x) minx=pcour->x;
            if (miny>pcour->y) miny=pcour->y;  
            pcour=pcour->suiv;
        }
    ccour=ccour->suiv;
    }
    SVGinit(&svg,nomInstance,500,500);
    ccour=C->chaines;
    while (ccour!=NULL){
        pcour=ccour->points;
        SVGlineRandColor(&svg);
        SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny)); 
        precx=pcour->x;
        precy=pcour->y;  
        pcour=pcour->suiv;
        while (pcour!=NULL){
            SVGline(&svg,500*(precx-minx)/(maxx-minx),500*(precy-miny)/(maxy-miny),500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            SVGpoint(&svg,500*(pcour->x-minx)/(maxx-minx),500*(pcour->y-miny)/(maxy-miny));
            precx=pcour->x;
            precy=pcour->y;    
            pcour=pcour->suiv;
        }
        ccour=ccour->suiv;
    }
    SVGfinalize(&svg);
}


double longueurChaine(CellChaine *c){
    CellChaine *tmp =c;
    double res=0;
    double x,y;
    CellPoint *tmp2=NULL;
    if(tmp==NULL){
        return res;
    }
    tmp2=tmp->points;
    if(tmp2==NULL){
        return res;
    }
    x=tmp2->x;
    y=tmp2->y;

    if(tmp2->suiv==NULL){
        return res;
    }

    tmp2=tmp2->suiv;

    while(tmp2){
        res+=sqrt((tmp2->x-x)*(tmp2->x-x)+(tmp2->y-y)*(tmp2->y-y));
        //printf("La distance calculee actuellement dans longueurChaine est %lf\n",sqrt((tmp2->x-x)*(tmp2->x-x)+(tmp2->y-y)*(tmp2->y-y)));
        x=tmp2->x;
        y=tmp2->y;
        
        tmp2=tmp2->suiv;
        
    }

    return res;
}

double longueurTotale(Chaines *C){
    double res=0;
    Chaines* tmp =C;
    if(tmp==NULL){
        return 0;
    }
    CellChaine *ctmp =tmp->chaines;
    if(ctmp==NULL){
        return 0;
    }

    while(ctmp){
        res+=longueurChaine(ctmp);
        //printf("Valeur actuelle de res : %lf\n",res);
        ctmp=ctmp->suiv;
    }

    return res;
}

int comptePointsTotal(Chaines *C){
    int cptocc=0;
    Chaines *tmpchaine=C;

    if(tmpchaine==NULL){
        return cptocc;
    }

    CellChaine* tmpcellc=tmpchaine->chaines;;
    if(tmpcellc==NULL){
        return cptocc;
    }

    while(tmpcellc){
        CellPoint *verifpoint=tmpcellc->points;
        while(verifpoint){
            cptocc++;
            verifpoint=verifpoint->suiv;
        }
        //printf("cpt a la fin du tour = %d\n",cptocc);
        tmpcellc=tmpcellc->suiv;
    }

    return cptocc;
}

void liberer_liste_points(CellPoint *p){
    if(p){
        CellPoint *tmp=NULL;
        while(p){
            tmp=p->suiv;
            free(p);
            p=tmp;
        }
    }
}
void liberer_cellChaine(CellChaine *c){
    if(c){
        CellChaine *tmp=NULL;
        while(c){
        liberer_liste_points(c->points);
        tmp=c->suiv;
        free(c);
        c=tmp;
        }
    }
}
void liberer_chaines(Chaines *c){
    if(c){
        liberer_cellChaine(c->chaines);
        free(c);
    }
}