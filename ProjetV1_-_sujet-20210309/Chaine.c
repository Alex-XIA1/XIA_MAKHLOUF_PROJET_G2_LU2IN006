#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "Chaine.h"

Chaines * lectureChaines(FILE* f){
    FILE* ptr =NULL;
    ptr = f;
    if(ptr==NULL){
        printf("Erreur d'ouverture du fichier\n");
        return NULL;
    }

    Chaines *res =malloc(sizeof(Chaines));
    res->chaines=NULL;

    char buffer[256];
    int num;
    int nbCh;
    float x;
    float y;

    fscanf(ptr,"%s %d",buffer,&res->gamma);
    printf("gamma = %d\n",res->gamma);
    /*fgets(buffer,256,ptr);
    buffer[strlen(buffer)-1]='\0';*/
    fscanf(ptr,"%s %d",buffer,&res->nbChaines);
    printf("chaines %d\n",res->nbChaines);
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
        printf("la valeur de ctmp = %d pour num = %d\n",cpt,num);
        fprintf(ptr,"%d %d ",num,cpt);

        CellPoint* ptmp=tmp2->points;
        while(ptmp){
            double x=ptmp->x;
            double y=ptmp->y;
            fprintf(ptr,"%.2f %.2f ",x,y);
            ptmp=ptmp->suiv;
            //printf("valeurs pour x : %.2f et y : %.2f\n",x,y);
        }
        tmp2=tmp2->suiv;
        //printf("ICI\n");
        fprintf(ptr,"\n");
    }

}