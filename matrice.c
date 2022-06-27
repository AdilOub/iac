#include <math.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "./matrice.h"

int printMatrice(Matrice *matrice)
{
    float *valeurs = matrice->valeurs;
    for (int i = 0; i < matrice->lignes; i++)
    {
        for (int j = 0; j < matrice->colones; j++)
        {
            printf("%f ", valeurs[i * matrice->colones + j]);
        }
        printf("\n");
    }
    printf("\n");
    return 0;
}


int initMatrice(Matrice *matrice, int lignes, int colones)
{
    matrice->lignes = lignes;
    matrice->colones = colones;

    float *valeurs = NULL;
    valeurs = malloc(sizeof(float) * lignes * colones);
    if (valeurs == NULL)
    {
        printf("Erreur d'allocation de mémoire");
        return -1;
    }

    memset(valeurs, 0, sizeof(float) * lignes * colones);
    matrice->valeurs = valeurs;
    return 0;
}

int setMatriceValue(Matrice *matrice, int ligne, int colonne, float value)
{
    matrice->valeurs[ligne * matrice->colones + colonne] = value;
    return 0;
}

float getMatriceValue(Matrice *matrice, int ligne, int colonne)
{
    return matrice->valeurs[ligne * matrice->colones + colonne];
}

int multiplyMatries(Matrice *result, Matrice *A, Matrice *B)
{
    initMatrice(result, A->lignes, B->colones);
    if (A->colones != B->lignes)
    {
        printf("Erreur : les matrices ne peuvent pas etre multipliees (colone A %d, ligne B %d).",A->colones, B->lignes );
        return -1;
    }

    // on multiplie toujours ai,j avec bj,i par paquet de colone pour avoir r

    for (int h = 0; h < A->lignes; h++)
    {
        for (int i = 0; i < B->colones; i++)
        {
            float sum = 0;
            for (int j = 0; j < A->colones; j++)
            {
                sum += A->valeurs[j+h*A->colones] * B->valeurs[j * B->colones + i];
            }
            result->valeurs[i + h*B->colones] = sum;
        }
    }

    return 0;
}

int addMatrice(Matrice *result, Matrice *A, Matrice *B){
    initMatrice(result, B->lignes, B->colones);
    if(A->colones != B->colones || A->lignes != B->lignes){
        printf("Impossible d'ajouter les deux matrices.\n");
        return -1;
    }
    for(int i = 0; i < A->lignes * A->colones; i++){
        result->valeurs[i] = A->valeurs[i] + B->valeurs[i];
    }
    return 0;
}
int subMatrice(Matrice *result, Matrice *A, Matrice *B){
    initMatrice(result, B->lignes, B->colones);
    if(A->colones != B->colones || A->lignes != B->lignes){
        printf("Impossible de soustraire les deux matrices.\n");
        return -1;
    }
    for(int i = 0; i < A->lignes * A->colones; i++){
        result->valeurs[i] = A->valeurs[i] - B->valeurs[i];
    }
    return 0;
}
int squareMatrcie(Matrice *result, Matrice *A){
    initMatrice(result, A->lignes, A->colones);
    for(int i = 0; i < A->lignes * A->colones; i++){
        result->valeurs[i] = A->valeurs[i] * A->valeurs[i];
    }
    return 0;
}

float sumOfMatrice(Matrice *A){
    float *valeurs = A->valeurs;
    float sum = 0;
    for (int i = 0; i < A->lignes; i++)
    {
        for (int j = 0; j < A->colones; j++)
        {
            sum += valeurs[i * A->colones + j];
        }
    }
    return sum;
}

int print1DArray(float array[], int size)
{
    printf("[");
    for (int i = 0; i < size; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("]\n");
    return 0;
}

int disposeMatrice(Matrice *matrice){
    matrice->colones = 0;
    matrice->lignes = 0;
    free(matrice->valeurs);
    return 0;
}

/*
int initialize2DArray(float **array, Matrice *matrice) {
    *array = malloc(sizeof(float) * matrice->lignes * matrice->colones);
    if(*array == NULL) {
        printf("Erreur d'allocation de mémoire");
        return -1;
    }
    memset(*array, 0, sizeof(float) * matrice->lignes * matrice->colones);
    return 0;
}

int matriceTo2DArray(Matrice *matrice, float **array) {
    printf("TODO !\n");
    return -1;
}*/