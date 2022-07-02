#ifndef MATRICE
#include "./matrice.h"
#endif

#ifndef IA 
#define IA
typedef struct Biais Biais;
struct Biais{
    int nbOfCouches;
    Matrice *biaisArray;
};


typedef struct Poids Poids;
struct Poids{
    int nbOfPoids;
    Matrice *poidsArray;
};

typedef struct Couches Couches;
struct Couches{
    int nbOfCouches;
    Matrice *MatriceList;
};



typedef struct Reseau Reseau;
struct Reseau{
    int nbNeuronneCoucheActivation;
    int nbNeuronneParCoucheIntermediaire;
    int nbNeuronneCoucheResultat;

    int nbOfCouchesIntermediaire;

    Couches couches;
    Poids poids;
    Biais biais;
};
#endif




int initReseau(Reseau *reseau, int nbCI, int nbNCA, int nbNCI, int nbNCR);
int initReseauWithFree(Reseau *reseau, int nbCI, int nbNCA, int nbNCI, int nbNCR);

int initCouches(Reseau *reseau, int size);
int initPoids(Reseau *reseau, int size);
int initBiais(Reseau *reseau, int size);

int printCouche(Reseau *reseau);
int printPoids(Reseau *reseau);
int printBiais(Reseau *reseau);

int guess(Reseau *reseau, Matrice *activation, Matrice *resultat);
float cost(Reseau *reseau, Matrice *activation, Matrice *resultatAttendu);
float costTotalMoyen(Reseau *reseau, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat);

int getNbOfPoidsBiais(Reseau *reseau);
float* poidAndBiaisIntolist(Reseau *reseau);

int createCloneOfValues(Reseau *reseau, float h, int index);
float deriveCostTotal(Reseau *reseau, float h, int param);
int registerListInReseau(Reseau *reseau, float *list, int NCA, int NCI, int nbCoucheInter, int NCR);

int slice(float *list, int min, int max, float *sliced);

float derivateIndex(Reseau *reseau, float h, int index, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat);
int derivateAllAndGetOppositOfGradient(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat, Matrice *gradient, int sizeOfGradient);

int train(Reseau *reseau, float h, Matrice* *activationList, Matrice* *resultatAttenduList, int nbOfResultat, int nbOfTraining, float step);