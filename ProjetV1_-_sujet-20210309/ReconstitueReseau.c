#include "Reseau.h"
#include "Chaine.h"
#define LONGUEURE_LIGNE 256
int main(){
    /*printf("Bonjour et Bienvenu\n");
    printf("Veuillez saisir la methode de votre choix parmi les suivantes\n");
    printf("Liste chainne : tapez 1\ntable de hachage : tapez 2\narbres : tapez 3\n ");
    char buffer[LONGUEURE_LIGNE];
    int choix;
    fgets(buffer,LONGUEURE_LIGNE,stdin);
    sscanf(buffer,"%d",&choix);
    FILE *pf=fopen("00014_burma.cha","r");
    if(pf==NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(-1);
    }
    Chaines*liste=lectureChaines(pf);
    switch (choix){
        case 1:
            printf("Votre choix: Liste chainee\n");
            Reseau *r=reconstitueReseauListe(liste);
            liberer_reseau(r);
            break;
        case 2:
            break;  
        case 3:
            break;
        default :
            printf("Numero de methode incorrect\n");
            exit(-1);
            break;
    }
    liberer_chaines(liste);
    fclose(pf);*/
    //printf("go\n");
    FILE *pf=fopen("00014_burma.cha","r");
    if(pf==NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(-1);
    }
    Chaines *liste=lectureChaines(pf);
    Reseau *res=reconstitueReseauListe(liste);
    liberer_reseau(res);
    liberer_chaines(liste);
    fclose(pf);
    return 0;
}