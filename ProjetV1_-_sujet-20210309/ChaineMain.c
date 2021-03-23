#include "Chaine.h"

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

    ecrireChaines(test,fp2);
    fclose(fp);
    fclose(fp2);
    return 0;
}