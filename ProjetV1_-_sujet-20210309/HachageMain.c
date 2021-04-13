#include "Hachage.h"
#include "SVGwriter.h"
int main(){
    srand(time(NULL));
    int xtest=3;
    int ytest=5;
    int cleft= foncK(xtest,ytest);
    //int tailletest=10;
    printf("La clef est %d\n", cleft);
    for(int i =0; i<10;i++){
        int xb=rand()%10+1;
        int yb=rand()%10+1;
        printf("La valeur de la clef dans la boucle pour x= %d et y= %d est %d\n",xb,yb,foncK(xb,yb));
    }
    //a tester plus tard
    //int ch=foncH(cleft,tailletest);
    //printf("La clef pour la taille de test est %d\n",ch);

    
    return 0;
}