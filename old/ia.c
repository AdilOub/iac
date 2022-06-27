#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "./ia.h"

int initReseau(Reseau *reseau, int activation, int intermerdiaire, int resultat, Matrice *CA, Matrice *CI, Matrice *CR, Matrice *PA, Matrice *PB, Matrice *BA, Matrice *BB){
    reseau->coucheActivationSize = activation;
    reseau->coucheIntermerdiaireASize = intermerdiaire;
    reseau->coucheResultatSize = resultat;
    
    if(initMatrice(CA, activation, 1) < 0 || initMatrice(CI, intermerdiaire, 1) < 0 || initMatrice(CR, resultat, 1) < 0){
        printf("Erreur lors de l'initialisation des colonnes de neuronnes.\n");
        return -1;
    }

    reseau->coucheActivation = CA;
    reseau->coucheIntermerdiaireA = CI;
    reseau->coucheResultat = CR;

    if(initMatrice(PA, intermerdiaire, activation) < 0 || initMatrice(PB, resultat, intermerdiaire) < 0){
        printf("Erreur lors de l'initialisation des matrices poids.\n");
        return -2;
    }

    if(initMatrice(BA, intermerdiaire, 1) < 0 || initMatrice(BB, resultat, 1) < 0){
        printf("Erreur lors de l'initialisation des matrices biais.\n");
        return -3;
    }

    reseau->poidsA = PA;
    reseau->poidsB = PB;
    reseau->biaisA = BA;
    reseau->biaisB = BB;
    
    return 0;
}


int printReseau(Reseau *reseau){
    printf("\nActivation:\n");
    printMatrice(reseau->coucheActivation);
    printf("Inter:\n");
    printMatrice(reseau->coucheIntermerdiaireA);
    printf("Resultat:\n");
    printMatrice(reseau->coucheResultat);
    printf("Poids A:\n");
    printMatrice(reseau->poidsA);
    printf("Biais A:\n");
    printMatrice(reseau->biaisA);
    printf("Poids B:\n");
    printMatrice(reseau->poidsB);
    printf("Biais B:\n");
    printMatrice(reseau->biaisB);
    return 0;
}