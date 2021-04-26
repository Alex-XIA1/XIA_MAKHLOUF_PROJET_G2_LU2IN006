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
    /*FILE*fp2=NULL;
    fp2=fopen("00014_burma2.res","w");
    if(fp2==NULL){
        printf("Erreur a l'ouverture du fichier\n");
        return 1;
    }*/

    //TODO
    FILE*ptrecrire=NULL;
    ptrecrire=fopen("Ex6_Q1.txt","w");
    if(ptrecrire==NULL){
        printf("Erreur d'ouverture\n");
        return 1;
    }

    /*
    //Rayane a decommente si besoin d'ecrire dans un fichier
    FILE*ptrq3=NULL;
    ptrq3=fopen("Ex6_Q3_G1.txt","w");
    if(ptrq3==NULL){
        printf("Erreur d'ouverture\n");
        return 1;
    }
    */

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
    //Reseau * resab=reconstitueReseauArbre(test);
    //afficheReseauSVG(resab,"EX5test");




    clock_t /*tinitL,tfinalL,*/tinitAb,tfinalAb,tinitH1,tfinalH1,tinitH2,tfinalH2;

    double /*tL,*/tAb,tH1,tH2;
    /*tinitL=clock();
    //resL=TEST ICI; //Rayane ajoute la fonction de reconstitution ici et decommente tinit,tfinal et t pour les listes
    tfinalL=clock();*/

    
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

    //Hachage pour taille 1000
    tinitH2=clock();
    Reseau* resH2=reconstitueReseauHachage(test,10000);
    tfinalH2=clock();
    tH2=((double)(tfinalH2-tinitH2))/CLOCKS_PER_SEC;
    

    //le 1 est temporaire
    //Rayane change la valeur 1.0 par la valeur que tu auras calculee + decommente
    //fprintf(ptrecrire,"%lf %lf %lf %lf\n",1.0,tH1,tH2,tAb);
    
    //TODO partie liste
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
        Reseau* resH1=reconstitueReseauHachage(chaineTmp,100);
        tfinalH1=clock();
        tH1=((double)(tfinalH1-tinitH1))/CLOCKS_PER_SEC;

        //printf("fini");
        //Hachage pour taille 10000
        tinitH2=clock();
        Reseau* resH2=reconstitueReseauHachage(chaineTmp,10000);
        tfinalH2=clock();
        tH2=((double)(tfinalH2-tinitH2))/CLOCKS_PER_SEC;

        fprintf(ptrq3bis,"%d %lf %lf %lf\n",i,tH1,tH2,tAb);

        //Fonctions a verifier
        liberer_chaines(chaineTmp);
        liberer_reseau(resAb);
        liberer_reseau(resH1);
        liberer_reseau(resH2);
        //Liberer chaque chaine en fin de boucle pour eviter les fuites TODO !!!!!
    }*/
    
   
    fclose(fp);
    //fclose(fp2);
    fclose(ptrecrire);
    //fclose(ptrq3);
    //fclose(ptrq3bis);
    return 0;
}