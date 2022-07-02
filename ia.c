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

int initReseauWithFree(Reseau *reseau, int nbCI, int nbNCA, int nbNCI, int nbNCR){
    const int NB_COUCHE_TOTAL = 2 + nbCI; //CA + nbCI + CR

    //printf("clearing...\n");
    //clear all matrice in reseau
    for(int i = 0; i<reseau->couches.nbOfCouches;i++){
        //disposeMatrice(&reseau->couches.MatriceList[i]);
        //disposeMatrice(&reseau->biais.biaisArray[i]);
    }
    for(int i = 0; i <reseau->poids.nbOfPoids; i++){
        //disposeMatrice(&reseau->poids.poidsArray[i]);
    }

    free(reseau->couches.MatriceList);
    free(reseau->poids.poidsArray);
    free(reseau->biais.biaisArray);

    
    //MEMORY LEAK FINAL PAS DANS LES MALLOC MAIS DANS LES MATRICE INIT !!!
    //printf("MEM 0: %ld\n", getMemoryUsage());
    initCouches(reseau, NB_COUCHE_TOTAL);
    initPoids(reseau, NB_COUCHE_TOTAL);
    initBiais(reseau, NB_COUCHE_TOTAL);
    //printf("MEM 1: %ld\n", getMemoryUsage());
    return 0;
}

#pragma region sub_init_nomalloc
/*
int initCouchesNoMalloc(Reseau *reseau, int nbOfCouche){
    //free(reseau->couches.MatriceList); //au cas ou...
    reseau->couches.MatriceList = NULL;
    reseau->couches.nbOfCouches = nbOfCouche;
    reseau->couches.MatriceList = malloc(sizeof(Matrice) * nbOfCouche);
    if(reseau->couches.MatriceList == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->couches.MatriceList, 0, sizeof(Matrice) * nbOfCouche);
    initMatriceNoMalloc(&(reseau->couches.MatriceList[0]), reseau->nbNeuronneCoucheActivation, 1);
    for(int i = 1; i < nbOfCouche-1; i++){
        initMatriceNoMalloc(&(reseau->couches.MatriceList[i]), reseau->nbNeuronneParCoucheIntermediaire, 1);
    }
    initMatriceNoMalloc(&(reseau->couches.MatriceList[nbOfCouche-1]), reseau->nbNeuronneCoucheResultat, 1);
    return 0;
}

int initPoidsNoMalloc(Reseau *reseau, int nbOfCouche){
    //free(reseau->poids.poidsArray);
    reseau->poids.poidsArray=NULL;
    reseau->poids.nbOfPoids = nbOfCouche-1;
    reseau->poids.poidsArray = malloc(sizeof(Matrice) * nbOfCouche);
    if(reseau->poids.poidsArray == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->poids.poidsArray, 0, sizeof(Matrice) * reseau->poids.nbOfPoids );
    initMatriceNoMalloc(&(reseau->poids.poidsArray[0]), reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneCoucheActivation);
    for(int i = 1; i < reseau->poids.nbOfPoids -1; i++){
        initMatriceNoMalloc(&(reseau->poids.poidsArray[i]), reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneParCoucheIntermediaire);
    }
    initMatriceNoMalloc(&(reseau->poids.poidsArray[reseau->poids.nbOfPoids -1]), reseau->nbNeuronneCoucheResultat, reseau->nbNeuronneParCoucheIntermediaire);
    return 0;
}

int initBiaisNoMalloc(Reseau *reseau, int nbOfCouche){
    //free(reseau->biais.biaisArray);
    reseau->biais.biaisArray = NULL;
    reseau->biais.nbOfCouches = nbOfCouche; //WARNING: pas de biais pour la première couche
    reseau->biais.biaisArray = malloc(sizeof(Matrice) * nbOfCouche);
    if(reseau->biais.biaisArray == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->biais.biaisArray, 0, sizeof(Matrice) * nbOfCouche);
    initMatriceNoMalloc(&(reseau->biais.biaisArray[0]), reseau->nbNeuronneCoucheActivation, 1);
    for(int i = 1; i < nbOfCouche-1; i++){
        initMatriceNoMalloc(&(reseau->biais.biaisArray[i]), reseau->nbNeuronneParCoucheIntermediaire, 1);
    }
    initMatriceNoMalloc(&(reseau->biais.biaisArray[nbOfCouche-1]), reseau->nbNeuronneCoucheResultat, 1);
    return 0;
}*/

#pragma endregion sub_init_nomalloc


#pragma region sub_init

int initCouches(Reseau *reseau, int nbOfCouche){
    //free(reseau->couches.MatriceList); //au cas ou...
    
    reseau->couches.MatriceList = NULL;
    reseau->couches.nbOfCouches = nbOfCouche;

    reseau->couches.MatriceList = malloc(sizeof(Matrice) * nbOfCouche);

    if(reseau->couches.MatriceList == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->couches.MatriceList, 0, sizeof(Matrice) * nbOfCouche);


    initMatrice(&(reseau->couches.MatriceList[0]), reseau->nbNeuronneCoucheActivation, 1);

    for(int i = 1; i < nbOfCouche-1; i++){
        initMatrice(&(reseau->couches.MatriceList[i]), reseau->nbNeuronneParCoucheIntermediaire, 1);
    }

    initMatrice(&(reseau->couches.MatriceList[nbOfCouche-1]), reseau->nbNeuronneCoucheResultat, 1);

    return 0;
}

int initPoids(Reseau *reseau, int nbOfCouche){
    //free(reseau->poids.poidsArray);

    reseau->poids.poidsArray=NULL;
    reseau->poids.nbOfPoids = nbOfCouche-1;
    
    reseau->poids.poidsArray = malloc(sizeof(Matrice) * nbOfCouche);
    if(reseau->poids.poidsArray == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->poids.poidsArray, 0, sizeof(Matrice) * reseau->poids.nbOfPoids );

    initMatrice(&(reseau->poids.poidsArray[0]), reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneCoucheActivation);

    for(int i = 1; i < reseau->poids.nbOfPoids -1; i++){
        initMatrice(&(reseau->poids.poidsArray[i]), reseau->nbNeuronneParCoucheIntermediaire, reseau->nbNeuronneParCoucheIntermediaire);
    }

    initMatrice(&(reseau->poids.poidsArray[reseau->poids.nbOfPoids -1]), reseau->nbNeuronneCoucheResultat, reseau->nbNeuronneParCoucheIntermediaire);
    
    return 0;
}

int initBiais(Reseau *reseau, int nbOfCouche){
    //free(reseau->biais.biaisArray);

    reseau->biais.biaisArray = NULL;
    reseau->biais.nbOfCouches = nbOfCouche; //WARNING: pas de biais pour la première couche

    reseau->biais.biaisArray = malloc(sizeof(Matrice) * nbOfCouche);
    if(reseau->biais.biaisArray == NULL){
        printf("Erreur lors de l'allocation de mémoire pour la liste des matrices (couches)");
        return -1;
    }
    memset(reseau->biais.biaisArray, 0, sizeof(Matrice) * nbOfCouche);

    initMatrice(&(reseau->biais.biaisArray[0]), reseau->nbNeuronneCoucheActivation, 1);

    for(int i = 1; i < nbOfCouche-1; i++){
        initMatrice(&(reseau->biais.biaisArray[i]), reseau->nbNeuronneParCoucheIntermediaire, 1);
    }

    initMatrice(&(reseau->biais.biaisArray[nbOfCouche-1]), reseau->nbNeuronneCoucheResultat, 1);
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
        
    float somme = sumOfMatrice(&coutSquared);

    disposeMatrice(&coutSub);
    disposeMatrice(&coutSquared);

    return somme;
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

int createCloneOfValues(Reseau *reseau, float h, int index){ //no leak inside
    float* listPoidBiais = NULL;
    listPoidBiais = poidAndBiaisIntolist(reseau);
    listPoidBiais[index] += h;
    registerListInReseau(reseau, listPoidBiais, reseau->nbNeuronneCoucheActivation, reseau->nbNeuronneParCoucheIntermediaire, reseau->nbOfCouchesIntermediaire, reseau->nbNeuronneCoucheResultat); //memory leak here
    
    free(listPoidBiais);

    return 0;
}

float derivateIndex(Reseau *reseau, float h, int index, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat){ //4kb leak 1/4

    float* oldValue = poidAndBiaisIntolist(reseau);
    createCloneOfValues(reseau, h, index); //MEMORY LEAK HERE BUT NOT IN FUNCTION

    float coutPlusH = costTotalMoyen(reseau, activationList, resultatAttenduList, nbOfResultat);

    if(coutPlusH<0){
        printf("Erreur dans la derive, costTotalMoyen negatif");
        return -1;
    }
    
    registerListInReseau(reseau, oldValue, reseau->nbNeuronneCoucheActivation, reseau->nbNeuronneParCoucheIntermediaire, reseau->nbOfCouchesIntermediaire, reseau->nbNeuronneCoucheResultat);

    float cout = costTotalMoyen(reseau, activationList, resultatAttenduList, nbOfResultat);

    free(oldValue);

    return (coutPlusH-cout)/h;
}


//memory leak 16kb
int derivateAllAndGetOppositOfGradient(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat, Matrice *gradient, int sizeOfGradient){

    //printf("MEM 0: %ld\n", getMemoryUsage());
    for(int i = 0; i<sizeOfGradient; i++){
        gradient->valeurs[i] = -derivateIndex(reseau, h, i, activationList, resultatAttenduList, nbOfResultat); //MEMORY LEACK HERE TODO 16kb
    }           
    //printf("MEM 1: %ld\n", getMemoryUsage());

    
    return 0;
}

int train(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat, int nbOfTraining, float step){
    //on calcule le gradient et on change les params de step, puis on recommence jusqu'a ce qu'on dépasse nbOftraining
    const int NCA = reseau->nbNeuronneCoucheActivation;
    const int NCI = reseau->nbNeuronneParCoucheIntermediaire;
    const int NCR = reseau->nbNeuronneCoucheResultat;
    const int nbCI = reseau->nbOfCouchesIntermediaire;

        Matrice gradient;
        const int size = getNbOfPoidsBiais(reseau);
        initMatrice(&gradient, size, 1);
   
    for(int trainingLoop = 0; trainingLoop < nbOfTraining; trainingLoop++){
        printf("Entrainement %d/%d.\n", trainingLoop+1, nbOfTraining);


        //on calcule le gradient que l'on multiplie par step
        clearMatrice(&gradient);

        derivateAllAndGetOppositOfGradient(reseau, h, activationList, resultatAttenduList, nbOfResultat, &gradient, size);         //LA FUITE DE MEMOIRE EST ICI

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
        //disposeMatrice(&gradient);
        disposeMatrice(&allValue);
        disposeMatrice(&result);

    }
    printf("Fin de l'entrainement !\n");
    return 0;
}


/*
float deriveCostTotal(Reseau *reseau, float h, int param){
    float* listPoidsBiais = NULL;
    listPoidsBiais = poidAndBiaisIntolist(reseau);
    if(listPoidsBiais == NULL){
        printf("Erreur: impossible d'obtenir la liste poids et biais");
        return -1;
    }

}*/

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

int slice(float *list, int min, int max, float *sliced){

    if(min > max){
        printf("Erreur impossible de couper la liste, min > max.\n");
        return -1;
    }

    int size = max - min;

    for(int i = 0; i < size; i++){
        sliced[i] = list[min+i];
    }

    return 0;
}


//MEMORY LEAK FINAL!!!!
int registerListInReseau(Reseau *reseau, float *list, int NCA, int NCI, int nbCoucheInter, int NCR){ //NCA = nombre de neuronne dans la couche d'activation...    
    /*printf("BEFORE\n");
    printPoids(reseau); TODO REMOVE DEBUG
    printf("\nLIST:\n");
    print1DArray(list, getNbOfPoidsBiais(reseau));*/
    const int NB_COUCHE_TOTAL = 2 + nbCoucheInter; //LA FUITE DE MEMOIRE EST DU A CA !!!!
    
    initReseauWithFree(reseau, nbCoucheInter, NCA, NCI, NCR);


    int index = 0;
    int indexPoids = 0;
    int indexBiais = 0;
    
    slice(list, 0, NCI*NCA, reseau->poids.poidsArray[indexPoids].valeurs); //1+ car la dernière est exclu
    indexPoids++;
    index += NCI*NCA;

    slice(list, index, index+NCI, reseau->biais.biaisArray[indexBiais].valeurs);

    indexBiais++;
    index+=NCI;

    if(nbCoucheInter>1){

        for(int i = 0; i<nbCoucheInter-1; i++){
            
            slice(list, index, index + NCI*NCI, reseau->poids.poidsArray[indexPoids].valeurs);
            indexPoids++;
            index+=NCI*NCI;

            slice(list, index, index+ NCI, reseau->biais.biaisArray[indexBiais].valeurs);
            indexBiais++;
            index += NCI;
        }
    }

    slice(list, index, index + NCR*NCI, reseau->poids.poidsArray[indexPoids].valeurs);
    indexPoids++;
    index += NCR*NCI;

    slice(list, index,index + NCR, reseau->biais.biaisArray[indexBiais].valeurs);
    indexBiais++;
    index += NCR;

    //printf("AFTER\n");
    //printPoids(reseau);
    return 0;
}

//TODO REPLACE MEMSET WITH MY MEMSET RANDOM !
//TODO REGLER LA MEMORY LEAK QUI EMPECHE DE TROP LOOP
//TODO ADD FUNCTION TO LOAD POIDS ET BIAIS