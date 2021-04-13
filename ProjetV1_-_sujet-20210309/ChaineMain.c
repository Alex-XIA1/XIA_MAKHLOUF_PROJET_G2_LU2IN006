#include "Chaine.h"
#include "SVGwriter.h"
#include "Hachage.h"

int main(){
    FILE *fp=NULL;
    fp=fopen("00014_burma.cha","r");
    if(fp ==NULL){
        printf("Erreur a l'ouverture du fichier");
        return 1;
    }
    FILE*fp2=NULL;
    fp2=fopen("00014_burma2.res","w");
    if(fp2==NULL){
        printf("Erreur a l'ouverture du fichier");
        return 1;
    }
    Chaines* test=NULL;
    test=lectureChaines(fp);
    //printf("gamma = %d\n",test->gamma);

    //On commente ecrireChaines et afficheCHainesSVG pour eviter la recreation a chaque execution
    //ecrireChaines(test,fp2);

    //afficheChainesSVG(test,"Question1_3");
    double q1n=longueurTotale(test);
    printf("La longueur totale de toutes les chaines de la question 1 est egale a %lf unite inconnue\n",q1n);

    int nbocc=comptePointsTotal(test);
    printf("Le nombre de points du reseau de la question 1 est : %d\n",nbocc);
    Reseau * res=reconstitueReseauHachage(test,100);
    //afficheReseauHSVG(res,"EX4_Q4_5");
    //afficheReseauHSVG(res,"verification");


    fclose(fp);
    fclose(fp2);
    return 0;
}