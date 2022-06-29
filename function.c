#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "./matrice.h"
#include "./function.h"

float sigmoid(float x){
    return 1/(1+exp(-x));
}

Matrice sigmoidMatrice(Matrice *matrice){
    Matrice resultat;
    if(initMatrice(&resultat, matrice->lignes, matrice->colones)<0){
        printf("Erreur lors de l'application de la sigmoid à la matrice");
        return resultat;
    }
    for(int i = 0; i < matrice->colones * matrice->lignes; i++){
        resultat.valeurs[i] = sigmoid(matrice->valeurs[i]);
    }
    return resultat;
}

float square(float x){
    return x*x;
}
