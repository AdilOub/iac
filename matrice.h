#ifndef MATRICE 
#define MATRICE
typedef struct Matrice Matrice;
struct Matrice{
    int lignes;
    int colones;
    float *valeurs;
};

typedef struct MatriceDim MatriceDim;
struct MatriceDim{
    int lignes;
    int colones;
};
#endif


int printMatrice(Matrice *matrice);
int initMatrice(Matrice *matrice, int lignes, int colones);

int setMatriceValue(Matrice *matrice, int ligne, int colonne, float value);
float getMatriceValue(Matrice *matrice, int ligne, int colonne);

int multiplyMatries(Matrice *result, Matrice *A, Matrice *B);
int addMatrice(Matrice *result, Matrice *A, Matrice *B);
int subMatrice(Matrice *result, Matrice *A, Matrice *B);
int squareMatrcie(Matrice *result, Matrice *A);
float sumOfMatrice(Matrice *A);
int multiplyByFloat(Matrice *matrice, float k);

int print1DArray(float array[], int size);
int multiplyListByFloat(float* list, float k, int size);
//float* matriceColoneToList(Matrice *matriceColone);

int disposeMatrice(Matrice *matrice);

/*
int initialize2DArray(float **array, Matrice *matrice);
int matriceTo2DArray(Matrice *matrice, float **array);
*/
