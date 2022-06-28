#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "./main.h"
#include "./matrice.h"
#include "./image.h"
#include "./function.h"
#include "./ia.h"

int main() {
    printf("Welcome !!\n");
    Reseau reseau;


    if(initReseau(&reseau, 1, 3, 2, 1) < 0){
        printf("Error !");
        return -1;
    }
    

    printf("CHANGEMENT DE POIDS: \n");
    float newpoidsA[6] = {0.2,0.4,-2,0.4,0.1,2};
    reseau.poids.poidsArray[0].valeurs = newpoidsA;
    float newpoidsB[4] = {4,2,6,12};
    reseau.poids.poidsArray[1].valeurs = newpoidsB;

    Matrice Devine;
    float devineArray[3] = {0.0,0.1,0.4};
    initMatrice(&Devine, 3, 1);
    Devine.valeurs = devineArray;


    debugAll(&reseau);

    Matrice resultat;
    guess(&reseau, &Devine, &resultat);
    printf("\nResultat de l'IA:\n");
    printMatrice(&resultat);

    Matrice resultatAttendu;
    float valeursAttendu[1] = {0.25};
    initMatrice(&resultatAttendu, 1, 1);
    resultatAttendu.valeurs = valeursAttendu;
    printf("COST:\n");
    float cout = cost(&reseau, &Devine, &resultatAttendu);
    printf("le coup est de: %f\n", cout);

    float *list = NULL;
    list = poidAndBiaisIntolist(&reseau);
    print1DArray(list, getNbOfPoidsBiais(&reseau));
    return 0;
}

int debugAll(Reseau *reseau){
    printCouche(reseau);
    printf("COUCHE OK !\n");
    printPoids(reseau);
    printf("POIDS OK !\n");
    printBiais(reseau);
    printf("BIAIS OK !\n");
    return 0;
}

//cls;gcc main.c function.c matrice.c ia.c -o main;./main