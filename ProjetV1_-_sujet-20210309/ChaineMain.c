#include "Chaine.h"

int main(){
    FILE *fp=NULL;
    fp=fopen("00014_burma.cha","r");
    if(fp ==NULL){
        printf("Erreur a l'ouverture du fichier");
    }
    Chaines* test;
    test=lectureChaines(fp);
    printf("gamma = %d\n",test->gamma);
    fclose(fp);
    return 0;
}