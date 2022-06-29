#ifndef IA 
#define IA
#endif

#ifndef MATRICE
#include "./matrice.h"
#endif

typedef struct Reseau Reseau;
struct Reseau{
    int coucheActivationSize;
    int coucheIntermerdiaireASize;
    int coucheResultatSize;

    Matrice *coucheActivation;
    Matrice *coucheIntermerdiaireA;
    Matrice *coucheResultat;

    Matrice *poidsA;
    Matrice *poidsB;

    Matrice *biaisA;
    Matrice *biaisB;
};

int initReseau(Reseau *reseau, int activation, int intermerdiaire, int resultat, Matrice *CA, Matrice *CI, Matrice *CR, Matrice *PA, Matrice *PB, Matrice *BA, Matrice *BB);
int printReseau(Reseau *reseau);