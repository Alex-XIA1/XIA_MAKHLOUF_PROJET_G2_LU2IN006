#include "Reseau.h"
int main(int argc,char *argv[]){
    printf("Bonjour et Bienvenu\n");
    printf("Veuillez saisir le nom du fichier a lire ainsi que la methode de votre choix parmi les suivantes\n");
    printf("Liste chainne : tapez 1\ntable de hachage : tapez 2\narbres : tapez 3\n ");
    if(argc!=3){
        printf("Nombre de parametres incorrects\nVeuillez joindre le nom du fichier ainsi que le numero de la methode\n");
        exit(-1);
    }
    FILE *pf=fopen("00014_burma.cha","r");
    Chaines*liste=lectureChaines(pf);
    if(pf==NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(-1);
    }
    int choix=atoi(argv[1]);
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
    fclose(pf);
    return 0;
}