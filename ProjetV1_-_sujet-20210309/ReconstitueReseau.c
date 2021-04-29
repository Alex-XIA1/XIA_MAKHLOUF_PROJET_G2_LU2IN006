#include "Reseau.h"
#include "Chaine.h"
#include "Graphe.h"
#include "Hachage.h"
#include "ArbreQuat.h"
#define LONGUEURE_LIGNE 256
int main(){

    // Tests pour le fichier reseau.c
    
    printf("Bonjour et Bienvenu\n");
    printf("Veuillez saisir la methode de votre choix parmi les suivantes ainsi que le nom du fichier \n");
    printf("Liste chainne : tapez 1\ntable de hachage : tapez 2\narbres : tapez 3\n ");
    char buffer[LONGUEURE_LIGNE];
    int choix;
    int M;
    char fichier[LONGUEURE_LIGNE];
    Reseau *r=NULL;
    fgets(buffer,LONGUEURE_LIGNE,stdin);
    sscanf(buffer, "%d",&choix);
    printf("Nom du fichier: ");
    fgets(buffer,LONGUEURE_LIGNE,stdin);
    sscanf(buffer,"%s",fichier);
    FILE *pf=fopen(fichier,"r");
    if(pf==NULL){
        printf("Erreur d'ouverture du fichier\n");
        exit(-1);
    }
    Chaines *liste=lectureChaines(pf);
    switch (choix){
        case 1:
            printf("Votre choix: Liste chainee\n");
            r=reconstitueReseauListe(liste);
            break;
        case 2:
            printf("Votre choix: table de hachage\n");
            printf("Veuillez saisir la taille de la table de hachage souhaitee\n");
            fgets(buffer,LONGUEURE_LIGNE,stdin);
            sscanf(buffer,"%d",&M);
            printf("Valeur OK\n");
            r=reconstitueReseauHachage(liste,M);
            break;  
        case 3:

            printf("Votre choix: Arbres\n");
            r=reconstitueReseauArbre(liste);
            printf("OK\n");
            break;
        default :
            printf("Numero de methode incorrect\n");
            exit(-1);
            break;
    }
    liberer_chaines(liste);
    fclose(pf);
    FILE *pf2=fopen("Ex3_qst3_test3.txt","w");
    
    if(pf2==NULL){
        printf("Erreur d'ouverture du fichier\n");
        return -1;
    }
    ecrireReseau(r,pf2);
    
    //afficheReseauSVGL2(res, "reconstitueReseauListeEx2");

    // Tests pour le fichier Graphe.c

    //Graphe *g=creerGraphe(r);
    //int d=plus_petit_nombre_aretes(g,g->T_som[0]->num-1,g->T_som[6]->num-1);
    //printf("d= %d\n",d);
    printf("OK\n");
    int reorganisation=reorganiseReseau(r);
    
    if(reorganisation==1)
        printf("La reorganisation du reseau a ete faite avec succes\n");
    else
        printf("Echec de la reorganisation du reseau\n");

    liberer_reseau(r);
    return 0;
}