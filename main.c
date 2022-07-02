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



#ifdef __linux__
#include <sys/resource.h>
long getMemoryUsage(){
    struct rusage myUsage;

    getrusage(RUSAGE_SELF, &myUsage);
    return myUsage.ru_maxrss;
}
#endif

#define EPSILON 1e-10 //TODO CHANGE




int main() {
    printf("Welcome !!\n");

    #ifdef __linux__
    printf("\nMemory usage: %ld", getMemoryUsage());
    #endif

    Reseau reseau;

    if(initReseau(&reseau, 2, 3, 2, 1) < 0){
        printf("Error !");
        return -1;
    }
    
     
    #ifdef __linux__
    long memInit = getMemoryUsage();
    printf("\nMemory initialized: %ld", memInit);
    #endif

    printf("CHANGEMENT DE POIDS:\n");
    float newpoidsA[6] = {1,0.1,-10,0.10,0.111,111};
    reseau.poids.poidsArray[0].valeurs = newpoidsA;
    float newpoidsB[4] = {2,2,2,2};
    reseau.poids.poidsArray[1].valeurs = newpoidsB;
    float newpoidsFinal[4] = {-5,4};
    reseau.poids.poidsArray[2].valeurs = newpoidsFinal;

    float biaisC2[2] = {2,2};
    float biaisC3[2] = {3,3};
    float biaisC4[1] = {4};

    reseau.biais.biaisArray[1].valeurs = biaisC2;
    reseau.biais.biaisArray[2].valeurs = biaisC3;
    reseau.biais.biaisArray[3].valeurs = biaisC4;

    #pragma region debug
    Matrice Devine;
    float devineArray[3] = {0.1,0.8,0.25};
    initMatrice(&Devine, 3, 1);
    Devine.valeurs = devineArray;


    debugAll(&reseau);

    Matrice resultat;
    guess(&reseau, &Devine, &resultat);
    printf("\nResultat de l'IA:\n");
    printMatrice(&resultat);

    Matrice resultatAttenduDebug;
    float valeursAttendu[1] = {0.25};
    initMatrice(&resultatAttenduDebug, 1, 1);
    resultatAttenduDebug.valeurs = valeursAttendu;
    printf("COST:\n");
    float coutAVANT = cost(&reseau, &Devine, &resultatAttenduDebug);
    printf("le coup est de: %f\n", coutAVANT);
    #pragma endregion debug
    



    Matrice resultatAttendu;
    float resultatAttenduValue[1] = {0.333};
    initMatrice(&resultatAttendu, 1, 1);
    resultatAttendu.valeurs = resultatAttenduValue;
    Matrice resultatAttendu2;
    float resultatAttenduValue2[1] = {0.99};
    initMatrice(&resultatAttendu2, 1, 1);
    resultatAttendu2.valeurs = resultatAttenduValue2;
    Matrice* resultatAttenduList[2] = {&resultatAttendu, &resultatAttendu2};
    
    Matrice activation1;
    float activation1Array[3] = {0.1,0.8,0.25};
    initMatrice(&activation1, 3, 1);
    activation1.valeurs = activation1Array;
    Matrice activation2;
    float activation1Array2[3] = {0.9,0.4,0.99};
    initMatrice(&activation2, 3, 1);
    activation2.valeurs = activation1Array2;
    Matrice* activationList[2] = {&activation1, &activation2};

    train(&reseau, EPSILON, activationList, resultatAttenduList, 2, 2, 0.1); //1000 -> coutAPRES 0.137770  10000 -> coutAPRES 0.145339  coutAPRES 0.159229 coutAPRES 0.001552

    printf("\n\nRESAU APRES TRAINING:\n");
    debugAll(&reseau);
    printf("\n-----------\n");


    float coutAPRES = cost(&reseau, &Devine, &resultatAttenduDebug);
    printf("COUP AVANT %f, coutAPRES %f", coutAVANT, coutAPRES);
    #ifdef __linux__
    printf("\nMemory usage: %ld\n", getMemoryUsage());
    printf("Difference: %d", getMemoryUsage()-memInit);
    #endif
    return 0;
}

int debugAll(Reseau *reseau){
    printf("Debug:\n");
    printCouche(reseau);
    printf("COUCHE OK !\n");
    printPoids(reseau);
    printf("POIDS OK !\n");
    printBiais(reseau);
    printf("BIAIS OK !\n");
    printf("Fin du debug.\n");
    return 0;
}

//cls;gcc main.c function.c matrice.c ia.c -o main;./main
//TODO BUG AVEC TROP DE BOUCLE + NAN



/*
Poids d'activation:
0.999992 0.099993 -10.000003
0.100000 0.111000 111.000000

Poids Intermediaire num.1 :
1.999954 1.999190
2.000059 2.000653

Poids des resultats:
-4.998385 4.001602

POIDS OK !

Biais Intermediaire num.1 :
0.000005
0.000000

Biais Intermediaire num.2 :
-0.000084
0.000000

Biais des resultats:
0.000000
*/

/*
Poids d'activation:
1.000000 0.100000 -10.000000
0.100000 0.111000 111.000000

Poids Intermediaire num.1 :
1.999985 1.991953
2.000000 2.006332

Poids des resultats:
-4.986604 4.013456

POIDS OK !

Biais Intermediaire num.1 :
0.000000
0.000000

Biais Intermediaire num.2 :
-0.000864
0.000000

Biais des resultats:
0.000000*/