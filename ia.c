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
        printf("on init %d\n",i)
;        Matrice matriceInter;
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
        Matrice resultDeLaMultiplication;
        Matrice resultDeLaddition;


        if(multiplyMatries(&resultDeLaMultiplication, &reseau->poids.poidsArray[i], &reseau->couches.MatriceList[i])<0){
            printf("\nErreur lors de la multiplication de la couche %d\n", i);
            return -1;
        }

        //on ajoute les biais
        if(addMatrice(&resultDeLaddition, &resultDeLaMultiplication, &reseau->biais.biaisArray[i+1])<0){ 
            printf("Erreur lors de l'addition des matrices pour guess.\n");
            return -1;
        }
        disposeMatrice(&resultDeLaMultiplication);
        reseau->couches.MatriceList[i+1] = sigmoidMatrice(&resultDeLaddition);
        disposeMatrice(&resultDeLaddition);
    }


    initMatrice(resultat, reseau->nbNeuronneCoucheResultat, 1);
    resultat->valeurs = reseau->couches.MatriceList[NB_OF_COUCHE-1].valeurs;
    return 0;
}

float cost(Reseau *reseau, Matrice *activation, Matrice *resultatAttendu){
    const int NB_OF_COUCHE = reseau->nbOfCouchesIntermediaire + 2;
    Matrice resultatObtenue;
    if(guess(reseau, activation, &resultatObtenue)<0){
        printf("Impossible de deviner, donc on peut pas calculer le coup.\n");
        return -1;
    }
    if(resultatAttendu->colones != resultatObtenue.colones || resultatAttendu->lignes != resultatObtenue.lignes){
        printf("Impossible de calculer le coup, les deux matrices n'ont pas la meme taille.\n");
        return -1;
    }

    Matrice coutSub;
    Matrice coutSquared;
    subMatrice(&coutSub, resultatAttendu, &resultatObtenue);
    squareMatrcie(&coutSquared, &coutSub);
    disposeMatrice(&coutSub);
    return sumOfMatrice(&coutSquared);
}

float costTotalMoyen(Reseau *reseau, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat){
    float coutT = 0;
    for(int i = 0; i < nbOfResultat; i++){
        float cout = cost(reseau, activationList[i], resultatAttenduList[i]);
        if(cout<0){
            printf("Erreur lors du calcule du coup n%d.\n",i);
            return -1;
        }
        coutT += cout;
    }
    return coutT/nbOfResultat;
}

float* createCloneOfValues(Reseau *reseau, float h, int index){
    float* listPoidBiaisWithoutChange = NULL;
    float* listPoidBiais = NULL;
    listPoidBiaisWithoutChange = poidAndBiaisIntolist(reseau);
    listPoidBiais = poidAndBiaisIntolist(reseau);
    listPoidBiais[index] += h;
    registerListInReseau(reseau, listPoidBiais, reseau->nbNeuronneCoucheActivation, reseau->nbNeuronneParCoucheIntermediaire, reseau->nbOfCouchesIntermediaire, reseau->nbNeuronneCoucheResultat);
    return listPoidBiaisWithoutChange;
}

float derivateIndex(Reseau *reseau, float h, int index, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat){
    const int NCA = reseau->nbNeuronneCoucheActivation;
    const int NCI = reseau->nbNeuronneParCoucheIntermediaire;
    const int NCR = reseau->nbNeuronneCoucheResultat;
    const int nbCI = reseau->nbOfCouchesIntermediaire;

    float* oldValue = createCloneOfValues(reseau, h, index);
    float coutPlusH = costTotalMoyen(reseau, activationList, resultatAttenduList, nbOfResultat);
    if(coutPlusH<0){
        printf("Erreur dans la derive, costTotalMoyen negatif");
        return -1;
    }
    registerListInReseau(reseau, oldValue, NCA, NCI, nbCI, NCR);
    float cout = costTotalMoyen(reseau, activationList, resultatAttenduList, nbOfResultat);

    return (coutPlusH-cout)/h;
}

Matrice derivateAllAndGetOppositOfGradient(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat){
    const int size = getNbOfPoidsBiais(reseau);
    Matrice gradient;
    initMatrice(&gradient, size, 1);
    for(int i = 0; i<size; i++){
        gradient.valeurs[i] = -derivateIndex(reseau, h, i, activationList, resultatAttenduList, nbOfResultat);
    }
    return gradient;
}

int train(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat, int nbOfTraining, float step){
    //on calcule le gradient et on change les params de step, puis on recommence jusqu'a ce qu'on dépasse nbOftraining
    const int NCA = reseau->nbNeuronneCoucheActivation;
    const int NCI = reseau->nbNeuronneParCoucheIntermediaire;
    const int NCR = reseau->nbNeuronneCoucheResultat;
    const int nbCI = reseau->nbOfCouchesIntermediaire;
    for(int trainingLoop = 0; trainingLoop < nbOfTraining; trainingLoop++){
        printf("Entrainement %d/%d.\n", trainingLoop+1, nbOfTraining);
        //on calcule le gradient que l'on multiplie par step
        Matrice gradient;
        gradient = derivateAllAndGetOppositOfGradient(reseau, h, activationList, resultatAttenduList, nbOfResultat);
        multiplyByFloat(&gradient, step);

        //on transforme tout les poids et biais en une matrice colone
        float* listPoidsEtBiais = poidAndBiaisIntolist(reseau);
        Matrice allValue;
        initMatrice(&allValue, getNbOfPoidsBiais(reseau), 1);
        allValue.valeurs = listPoidsEtBiais;

        //on additionne les deux matrices
        Matrice result;
        if(addMatrice(&result, &allValue, &gradient)<0){
            printf("Erreur lors de l'addition des matrices poidsEtBiais et Gradient");
            return -1;
        }

        //on enrengistre les nouveaux poids et biais
        registerListInReseau(reseau, result.valeurs, NCA, NCI, nbCI, NCR);

        //on libère la RAM !
        disposeMatrice(&gradient);
        disposeMatrice(&allValue);
        disposeMatrice(&result);
    }
    printf("Fin de l'entrainement !\n");
}



float deriveCostTotal(Reseau *reseau, float h, int param){
    float* listPoidsBiais = NULL;
    listPoidsBiais = poidAndBiaisIntolist(reseau);
    if(listPoidsBiais == NULL){
        printf("Erreur: impossible d'obtenir la liste poids et biais");
        return -1;
    }

}

int getNbOfPoidsBiais(Reseau *reseau){
    const int NB_OF_COUCHE = reseau->nbOfCouchesIntermediaire+2;

    int nbOfPoids = 0;
    for(int i = 0; i < reseau->poids.nbOfPoids; i++){
        nbOfPoids += reseau->poids.poidsArray[i].colones*reseau->poids.poidsArray[i].lignes;
    }
    int nbOfBiais = 0;
    for(int i = 1; i < reseau->biais.nbOfCouches; i++){ //attention on touche pas à la première couche
        nbOfBiais += reseau->biais.biaisArray[i].lignes; //une seul colone
    }
    return nbOfPoids+nbOfBiais;
}

float* poidAndBiaisIntolist(Reseau *reseau){
    const int size = getNbOfPoidsBiais(reseau);
    float *list = NULL;
    list = malloc(sizeof(float) * (size));
    if(list == NULL){
        printf("Erreur lors de l'allocation de la memoire");
        return NULL;
    }
    
    int n = 0;
    for(int i = 0; i<reseau->poids.nbOfPoids; i++){
        for(int j = 0; j<reseau->poids.poidsArray[i].colones*reseau->poids.poidsArray[i].lignes; j++){
            list[n] = reseau->poids.poidsArray[i].valeurs[j];
            n++;
        }
        if(i<reseau->poids.nbOfPoids){
            for(int k=0; k<reseau->biais.biaisArray[i+1].colones* reseau->biais.biaisArray[i+1].lignes; k++){
                list[n] = reseau->biais.biaisArray[i+1].valeurs[k];
                n++;
            }
        }
    }
    return list;
}

float* slice(float *list, int min, int max){
    if(min > max){
        printf("Erreur impossible de couper la liste, min > max.\n");
        return NULL;
    }
    float* sliced = NULL;
    int size = max - min;
    sliced = malloc(sizeof(float) * size);
    for(int i = 0; i < size; i++){
        sliced[i] = list[min+i];
    }
    return sliced;
}

int registerListInReseau(Reseau *reseau, float *list, int NCA, int NCI, int nbCoucheInter, int NCR){ //NCA = nombre de neuronne dans la couche d'activation...
    int index = 0;
    Matrice poidsA;
    initMatrice(&poidsA, NCI, NCA);
    poidsA.valeurs = slice(list, 0, 1 + NCI*NCA); //1+ car la dernière est exclu (j'ai pas compris mais ça marche)
    index += NCI*NCA;

    Matrice biaisI1;
    initMatrice(&biaisI1, NCI, 1);
    biaisI1.valeurs = slice(list, index, index+NCI);
    index+=NCI;

        Matrice *biaisInterList = NULL;
        Matrice *poidsInterList = NULL;
    if(nbCoucheInter>1){

        biaisInterList = malloc(sizeof(Matrice) * nbCoucheInter);
        poidsInterList = malloc(sizeof(Matrice) * nbCoucheInter);
        if(poidsInterList == NULL || biaisInterList == NULL){
            printf("Erreur lors de l'allocation de mémoire pour la liste des matrices poids ou biais (in registerListInReseau).\n");
            return -1;
        }
        memset(poidsInterList, 0, sizeof(Matrice) * nbCoucheInter);
        memset(biaisInterList, 0, sizeof(Matrice) * nbCoucheInter);
        for(int i = 0; i<nbCoucheInter; i++){
            
            Matrice tempP;
            initMatrice(&tempP, NCI, NCI);
            tempP.valeurs = slice(list, index, index+ NCI*NCI);
            index+=NCI*NCI;
            poidsInterList[i] = tempP;

            Matrice tempB;
            initMatrice(&tempB, NCI, 1);
            tempB.valeurs = slice(list, index, index+ NCI);
            index += NCI;
            biaisInterList[i] = tempB;
        }
    }

    Matrice poidsFinal;
    initMatrice(&poidsFinal, NCR, NCI);
    poidsFinal.valeurs = slice(list, index, index+ NCR*NCI);
    index += NCR*NCI;

    Matrice biaisFinal;
    initMatrice(&biaisFinal, NCR, 1);
    biaisFinal.valeurs = slice(list, index,index+ NCR);
    index += NCR;
    
    reseau->poids.poidsArray[0] = poidsA;
    reseau->biais.biaisArray[1] = biaisI1;

    if(nbCoucheInter>1){
        for(int i = 1; i<nbCoucheInter; i++){
            reseau->poids.poidsArray[i] = poidsInterList[i];
            reseau->biais.biaisArray[i+1] = biaisInterList[i];
        }
    }
    reseau->poids.poidsArray[reseau->poids.nbOfPoids-1] = poidsFinal;
    reseau->biais.biaisArray[reseau->biais.nbOfCouches-1] = biaisFinal;

    return 0;
}

//TODO REPLACE MEMSET WITH MY MEMSET RANDOM !