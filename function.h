typedef struct Args Args;
struct Args{
    int nbOfArgs;
    float *args;
};



float sigmoid(float x);
float square(float x);
Matrice sigmoidMatrice(Matrice *matrice);