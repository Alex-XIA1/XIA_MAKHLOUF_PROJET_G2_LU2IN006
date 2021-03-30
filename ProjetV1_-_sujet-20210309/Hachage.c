#include "Hachage.h"


//On utilise la formule de l'enonce
int foncK(double x, double y){
    return (int)(y+(x+y)*(x+y+1)/2);
}

//On utilise la formule de l'enonce (qui est la meme que celle du mini projet 2)
int foncH(int key, int M){
    int res=0;
    //On calcule A
    double A= (sqrt(5)-1)/2;
    //Pour obtenir les parties entieres on cast en int
    res= (int)(M*(key*A-(int)(key*A)));
    return res;
}