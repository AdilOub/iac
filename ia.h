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
int initCouches(Reseau *reseau, int size);
int initPoids(Reseau *reseau, int size);
int initBiais(Reseau *reseau, int size);

int printCouche(Reseau *reseau);
int printPoids(Reseau *reseau);
int printBiais(Reseau *reseau);

int guess(Reseau *reseau, Matrice *activation, Matrice *resultat);
float cost(Reseau *reseau, Matrice *activation, Matrice *resultatAttendu);
float costTotalMoyen(Reseau *reseau, Matrice *activationList[], Matrice *resultatAttenduList[], int nbOfResultat);

int getNbOfPoidsBiais(Reseau *reseau);
float* poidAndBiaisIntolist(Reseau *reseau);