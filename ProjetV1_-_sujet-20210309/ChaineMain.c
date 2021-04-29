#include "Chaine.h"
#include "SVGwriter.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#include "Reseau.h"

int main(){
    FILE *fp=NULL;
    fp=fopen("00014_burma.cha","r");
    if(fp ==NULL){
        printf("Erreur a l'ouverture du fichier\n");
        return 1;
    }
    FILE *fppla=NULL;
    fppla=fopen("07397_pla.cha","r");
    if(fp ==NULL){
        printf("Erreur a l'ouverture du fichier\n");
        return 1;
    }
    /*FILE*fp2=NULL;
    fp2=fopen("00014_burma2.res","w");
    if(fp2==NULL){
        printf("Erreur a l'ouverture du fichier\n");
        return 1;
    }*/

    
    /*FILE*ptrecrire=NULL;
    ptrecrire=fopen("Ex6_Q1.txt","w");
    if(ptrecrire==NULL){
        printf("Erreur d'ouverture\n");
        return 1;
    }*/

    
    /*FILE*ptrq3=NULL;
    ptrq3=fopen("Ex6_Q3_G1.txt","w");
    if(ptrq3==NULL){
        printf("Erreur d'ouverture\n");
        return 1;
    }*/
    

    //Decommenter la boucle Ex6 question 3
    /*FILE*ptrq3bis=NULL;
    ptrq3bis=fopen("Ex6_Q3_G2.txt","w");
    if(ptrq3bis==NULL){
        printf("Erreur d'ouverture\n");
        return 1;
    }*/

    /*FILE*ptrtest=NULL;
    ptrtest=fopen("perm.cha","r");

    Chaines* unt=lectureChaines(ptrtest);
    Reseau*part=reconstitueReseauArbre(unt);
    afficheReseauSVG(part,"permtest");

    fclose(ptrtest);*/
    /*
    //Fonctionne!
    FILE*ptrtest=NULL;
    ptrtest=fopen("05000_USA-road-d-NY.cha","r");

    Chaines* unt=lectureChaines(ptrtest);
    Reseau*part=reconstitueReseauArbre(unt);
    fclose(ptrtest);*/

    Chaines* test=NULL;
    test=lectureChaines(fp);

    Chaines* test2=NULL;
    test2=lectureChaines(fp);

    //printf("gamma = %d\n",test->gamma);
    //liberer_chaines(test);
    //On commente ecrireChaines et afficheCHainesSVG pour eviter la recreation a chaque execution
    //ecrireChaines(test,fp2);

    //afficheChainesSVG(test,"Question1_3");
    
    //double q1n=longueurTotale(test);
    //printf("La longueur totale de toutes les chaines de la question 1 est egale a %lf unite inconnue\n",q1n);

    //int nbocc=comptePointsTotal(test);
    //printf("Le nombre de points du reseau de la question 1 est : %d\n",nbocc);
    //Reseau * res=reconstitueReseauHachage(test,100);
    //afficheReseauHSVG(res,"EX4_Q4_5");
    //afficheReseauHSVG(res,"verification");
    Reseau * resab=reconstitueReseauArbre(test);
    afficheReseauSVG(resab,"EX5test");
    Reseau* pla=reconstitueReseauHachage(test2,10000);




    clock_t tinitL,tfinalL,tinitAb,tfinalAb,tinitH1,tfinalH1,tinitH2,tfinalH2;

    double tL,tAb,tH1,tH2;
    tinitL=clock();
    Reseau *resL=reconstitueReseauListe(test);
    tfinalL=clock();
    tL=((double)(tfinalL-tinitL))/CLOCKS_PER_SEC;

    
    //Arbre Quat
    tinitAb=clock();
    Reseau* resAb=reconstitueReseauArbre(test);
    tfinalAb=clock();
    tAb=((double)(tfinalAb-tinitAb))/CLOCKS_PER_SEC;

    //Hachage pour taille 100
    tinitH1=clock();
    Reseau* resH1=reconstitueReseauHachage(test,100);
    tfinalH1=clock();
    tH1=((double)(tfinalH1-tinitH1))/CLOCKS_PER_SEC;

    //Hachage pour taille 10000
    tinitH2=clock();
    Reseau* resH2=reconstitueReseauHachage(test,10000);
    tfinalH2=clock();
    tH2=((double)(tfinalH2-tinitH2))/CLOCKS_PER_SEC;
    

    
    //fprintf(ptrecrire,"%lf %lf %lf %lf\n",tL,tH1,tH2,tAb);
    
    //Ex6 Question 3(partie Liste)
    /*for(int i=500;i<=5000;i+=500){
        Chaines* chaineTmpL=generationAleatoire(i,100,5000,5000); 

        tinitL=clock();
        Reseau *resL=reconstitueReseauListe(chaineTmpL);
        tfinalL=clock();
        tL=((double)(tfinalL-tinitL))/CLOCKS_PER_SEC;

        fprintf(ptrq3,"%d %lf\n",i,tL);
        //On utilise pas ces fonctions sinon le temps d'execution est trop long
        //liberer_chaines(chaineTmpL);
        //liberer_reseau(resL);
        chaineTmpL=NULL;
        resL=NULL;
        printf("Tour numero : %d\n",i);
    }*/
    //Ex6 Question 3(partie courbe table et arbre)


    /*for(int i=500;i<=5000;i+=500){
        Chaines* chaineTmp=generationAleatoire(i,100,5000,5000);        

        tinitAb=clock();
        Reseau* resAb2=reconstitueReseauArbre(chaineTmp); 
        printf("je passe l'arbre et i est %d \n",i);       
        tfinalAb=clock();
        tAb=((double)(tfinalAb-tinitAb))/CLOCKS_PER_SEC;

        //Hachage pour taille 100
        tinitH1=clock();
        Reseau* resH1_2=reconstitueReseauHachage(chaineTmp,100);
        tfinalH1=clock();
        tH1=((double)(tfinalH1-tinitH1))/CLOCKS_PER_SEC;

        //printf("fini");
        //Hachage pour taille 10000
        tinitH2=clock();
        Reseau* resH2_2=reconstitueReseauHachage(chaineTmp,10000);
        tfinalH2=clock();
        tH2=((double)(tfinalH2-tinitH2))/CLOCKS_PER_SEC;

        fprintf(ptrq3bis,"%d %lf %lf %lf\n",i,tH1,tH2,tAb);

        //Fonctions a verifier
        liberer_chaines(chaineTmp);
        liberer_reseau(resAb2);
        liberer_reseau(resH1_2);
        liberer_reseau(resH2_2);
        
    }*/
    liberer_chaines(test);
    liberer_reseau(resL);
    liberer_reseau(resAb);
    liberer_reseau(resH1);
    liberer_reseau(resH2);
    liberer_reseau(pla);
    fclose(fp);
    fclose(fppla);
    //fclose(fp2);
    //fclose(ptrecrire);
    //fclose(ptrq3);
    //fclose(ptrq3bis);
    return 0;
}