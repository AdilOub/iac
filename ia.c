#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "./ia.h"
#include "./function.h"

int initReseau(Reseau *reseau, int nbCI, int nbNCA, int nbNCI, int nbNCR){
    Poids poids;
    Biais biais;

    reseau->nbOfCouchesIntermediaire = nbCI;
    reseau->nbNeuronneCoucheActivation = nbNCA;
    reseau->nbNeuronneParCoucheIntermediaire = nbNCI;
    reseau->nbNeuronneCoucheResultat = nbNCR;

    const int NB_COUCHE_TOTAL = 2 + nbCI; //CA + nbCI + CR
    initCouches(reseau, NB_COUCHE_TOTAL);
    initPoids(reseau, NB_COUCHE_TOTAL);
    initBiais(reseau, NB_COUCHE_TOTAL);
    return 0;
}

#pragma region sub_init

int initCouches(Reseau *reseau, int nbOfCouche){
    Couches couches;
    couches.nbOfCouches = nbOfCouche;


    Matrice *matriceList = NULL;
    matriceList = malloc(sizeof(Matrice) * nbOfCouche);
    if(matriceList == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(matriceList, 0, sizeof(Matrice) * nbOfCouche);

    Matrice activation;
    initMatrice(&activation, reseau->nbNeuronneCoucheActivation, 1);
    matriceList[0] = activation;

    for(int i = 1; i < nbOfCouche-1; i++){
        Matrice matriceInter;
        initMatrice(&matriceInter, reseau->nbNeuronneParCoucheIntermediaire, 1);
        matriceList[i] = matriceInter;
    }

    Matrice resultat;
    initMatrice(&resultat, reseau->nbNeuronneCoucheResultat, 1);
    matriceList[nbOfCouche-1] = resultat;

    couches.MatriceList = matriceList;
    reseau->couches = couches;
    return 0;
}

int initPoids(Reseau *reseau, int nbOfCouche){
    Poids poids;
    poids.nbOfPoids = nbOfCouche-1; //IL Y A TOUJOURS UNE MATRICE EN MOINS
    
    Matrice *matriceList = NULL;
    matriceList = malloc(sizeof(Matrice) * poids.nbOfPoids);
    if(matriceList == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(matriceList, 0, sizeof(Matrice) * poids.nbOfPoids);

    Matrice activation;
    initMatrice(&activation, reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneCoucheActivation);
    matriceList[0] = activation;

    for(int i = 1; i < poids.nbOfPoids-1; i++){
        Matrice matriceInter;
        initMatrice(&matriceInter, reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneParCoucheIntermediaire);
        matriceList[i] = matriceInter;
    }

    Matrice resultat;
    initMatrice(&resultat, reseau->nbNeuronneCoucheResultat, reseau->nbNeuronneParCoucheIntermediaire);
    matriceList[poids.nbOfPoids-1] = resultat;
    
    poids.poidsArray = matriceList;
    reseau->poids = poids;
    return 0;
}

int initBiais(Reseau *reseau, int nbOfCouche){
    Biais biais;
    biais.nbOfCouches = nbOfCouche; //WARNING: pas de biais pour la première couche


    Matrice *matriceList = NULL;
    matriceList = malloc(sizeof(Matrice) * nbOfCouche);
    if(matriceList == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(matriceList, 0, sizeof(Matrice) * nbOfCouche);

    Matrice activation;
    initMatrice(&activation, reseau->nbNeuronneCoucheActivation, 1);
    matriceList[0] = activation;

    for(int i = 1; i < nbOfCouche-1; i++){
        Matrice matriceInter;
        initMatrice(&matriceInter, reseau->nbNeuronneParCoucheIntermediaire, 1);
        matriceList[i] = matriceInter;
    }

    Matrice resultat;
    initMatrice(&resultat, reseau->nbNeuronneCoucheResultat, 1);
    matriceList[nbOfCouche-1] = resultat;

    biais.biaisArray = matriceList;
    reseau->biais = biais;
    return 0;
}

#pragma endregion sub_init

#pragma region print

int printCouche(Reseau *reseau){
    printf("\nCouche d'activation: \n");
    printMatrice(&(reseau->couches.MatriceList[0]));
    for(int i = 1; i < reseau->couches.nbOfCouches-1; i++){
        printf("Couche Intermediaire num.%d :\n", i);
        printMatrice(&(reseau->couches.MatriceList[i]));
    }
    printf("Couche des resultats: \n");
    printMatrice(&(reseau->couches.MatriceList[reseau->couches.nbOfCouches-1]));
    return 0;
}

int printPoids(Reseau *reseau){
    printf("\nPoids d'activation: \n");
    printMatrice(&(reseau->poids.poidsArray[0]));
    for(int i = 1; i < reseau->poids.nbOfPoids-1; i++){
        printf("Poids Intermediaire num.%d :\n", i);
        printMatrice(&(reseau->poids.poidsArray[i]));
    }
    printf("Poids des resultats: \n");
    printMatrice(&(reseau->poids.poidsArray[reseau->poids.nbOfPoids-1]));
    return 0;
}

int printBiais(Reseau *reseau){
    printf("\nBiais d'activation (toujours nul): \n");
    printMatrice(&(reseau->biais.biaisArray[0]));
    for(int i = 1; i < reseau->biais.nbOfCouches-1; i++){
        printf("Biais Intermediaire num.%d :\n", i);
        printMatrice(&(reseau->biais.biaisArray[i]));
    }
    printf("Biais des resultats: \n");
    printMatrice(&(reseau->biais.biaisArray[reseau->biais.nbOfCouches-1]));
    return 0;
}
#pragma endregion print

int guess(Reseau *reseau, Matrice *activation, Matrice *resultat){
    const int NB_OF_COUCHE = reseau->nbOfCouchesIntermediaire + 2;
    if(activation->colones != reseau->couches.MatriceList[0].colones || activation->lignes != reseau->couches.MatriceList[0].lignes){
        printf("Erreur: La matrice d'activation n'a pas les bonnes dimensions");
        return -1;
    }
    reseau->couches.MatriceList[0] = *activation;

    //calculate next level:
    for(int i = 0; i < NB_OF_COUCHE-1; i++){ //suivant = poids * précendant + biais
        

        Matrice result;
        Matrice result2;
        if(multiplyMatries(&result, &reseau->poids.poidsArray[i], &reseau->couches.MatriceList[i])<0){
            printf("\nErreur lors de la multiplication de la couche %d\n", i);
            return -1;
        }
        addMatrice(&result2, &result, &reseau->biais.biaisArray[i+1]); //TODO ADD SIGMOID
        reseau->couches.MatriceList[i+1] = sigmoidMatrice(&result2);
    }
    initMatrice(resultat, reseau->nbNeuronneCoucheResultat, 1);
    resultat->valeurs = reseau->couches.MatriceList[NB_OF_COUCHE-1].valeurs;
    return 0;
}

float cost(Reseau *reseau, Matrice *activation, Matrice *resultatAttendu){
    const int NB_OF_COUCHE = reseau->nbOfCouchesIntermediaire + 2;
    Matrice resultatObtenue;
    guess(reseau, activation, &resultatObtenue);
    if(resultatAttendu->colones != resultatObtenue.colones || resultatAttendu->lignes != resultatObtenue.lignes){
        printf("Impossible de calculer le coup, les deux matrices n'ont pas la meme taille.\n");
        return -1;
    }

    Matrice coutSub;
    Matrice coutSq;
    subMatrice(&coutSub, resultatAttendu, &resultatObtenue);
    squareMatrcie(&coutSq, &coutSub);
    disposeMatrice(&coutSub);
    return sumOfMatrice(&coutSq);
}

float costTotalMoyen(Reseau *reseau, Matrice *activationList[], Matrice *resultatAttenduList[], int nbOfResultat){
    float cout = 0;
    for(int i = 0; i < nbOfResultat; i++){
        cout += cost(reseau, activationList[i], resultatAttenduList[i]);
    }
    return cout/nbOfResultat;
}

float poidAndBiaisIntolist(Reseau *reseau, float *list){
    const int NB_OF_COUCHE = reseau->nbOfCouchesIntermediaire+2;
    const int NB_OF_MATICE_POIDS = reseau->poids.nbOfPoids;
    int nbOfPoids = 0;
    for(int i = 0; i < NB_OF_MATICE_POIDS; i++){
        nbOfPoids += reseau->poids.poidsArray[i].colones*reseau->poids.poidsArray[i].lignes;
        //on a ajouté tout les poids mainteant on ajoute les biais
        
    }
    printf("Nb of poids %d.\n", nbOfPoids);
    return 0;
}