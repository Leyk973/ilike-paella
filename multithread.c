#include <stdio.h>
#include <stdlib.h> // srand, rand...
#include <math.h> // maths
#include <time.h> // clock
#include <pthread.h>


/**
 ** ptrTab = pointeur vers le tableau de nombres entré
 ** tabSize = nombre d'éléments dans le tableau
 **/

float MARIT (float * ptrTab, size_t tabSize)
{
    size_t i;

    float res=0;

    for (i = 1; i <= tabSize; ++i)
    {
        res += ptrTab[i];
    }

    res = res/tabSize;

    return res;

}

/**
 ** ptrTab = pointeur vers le tableau de nombres entré
 ** tabSize = nombre d'éléments dans le tableau
 **/

float MQUAD (float * ptrTab, size_t tabSize)
{
    size_t i;

    float res=0;

    float temp;

    for (i = 1; i <= tabSize; ++i)
    {
        temp = ptrTab[i];
        res += pow(temp,2);
    }

    res /= tabSize;
    res = sqrt(res);

    return res;

}

float SCUB (float * ptrTab, size_t tabSize)
{
    size_t i;

    float res=0;

    for (i = 1; i <= tabSize; ++i)
    {
        res += pow(ptrTab[i],3);
    }

    return res;

}

// structure contenant les arguments pour le calcul du bazar
// (tableau et taille du tableau rempli)
typedef struct {
    float * ptrTab;
    size_t tabSize;
}datatata ;


/*thread function 1 : mean*/
void * threadMean (void* arg)
{
    datatata *struData = (datatata*)arg;

    double* res;
    res = (double*)malloc(sizeof(double));
    *res = 0;

    size_t i;

    for (i = 1; i <= struData->tabSize; ++i)
    {
        //printf("iteration %d\n",i);
        *res += struData->ptrTab[i];
    }

    *res = *res/struData->tabSize;

    pthread_exit((void*)res);

    return NULL;

}


/*thread function 2 : squared mean*/
void * threadSqMean (void* arg)
{
    datatata *struData = (datatata*)arg;

    float res = 0;
    float temp;

    for (size_t i = 1; i <= struData->tabSize; ++i)
    {
        temp = struData->ptrTab[i];
        res += pow(temp,2);
    }

    res = res/struData->tabSize;
    res = sqrt(res);

    //printf("La moyenne quadratique vaut %f \n",res);

    return NULL;

}

/*thread function 3 : 3powSum*/
void * threadPowSum (void* arg)
{
    datatata *struData = (datatata*)arg;

    float res = 0;
    float temp;

    for (size_t i = 1; i <= struData->tabSize; ++i)
    {
        temp = struData->ptrTab[i];
        res += pow(temp,3);
    }

    //printf("La somme des cubes vaut %f \n",res);

    return NULL;

}



int main(void)
{
    // nombre d'itérations
    size_t nbIte=10;

//    printf("Combien d'iterations du programme ? : ");
//    scanf("%d",&nbIte);


    int N;
    printf("Valeur de N ? : ");
    scanf("%d",&N);

    //float iniTime = time(NULL);

    clock_t start, end;

    start = clock();



    for (size_t y = 0 ; y < nbIte ; ++y)
    {
        srand(time(NULL));


        int i = 1;
        int j = i;
        float T [N];

        //int limite = enne;
        //float scube;

        //double marit, mquad;

        // trois threads par t
        int NB_THREADS = 3*N;
        pthread_t threads [NB_THREADS];

        //argument pour threads
        datatata stArgs;
        stArgs.ptrTab=T;
        stArgs.tabSize=i;

        while (i <= N)
        {
            //float temp;
            //printf("Entrez la valeur %d : ",i);
            //scanf("%f",&T[i]);
            T[i] = rand();

            stArgs.ptrTab=T;
            stArgs.tabSize=i;

            double* moyenneUnPeu;

#if 0

            marit = MARIT(T,i);
            mquad = MQUAD(T,i);
            scube = SCUB(T,i);


            printf("La moyenne vaut %f \n",marit);
            printf("La moyenne quadratique vaut %f \n",mquad);
            printf("La somme des cubes vaut %f \n",scube);
#endif

            if (pthread_create(&threads[j], NULL, threadMean, (void*)&stArgs) != 0)
            {
              fprintf(stderr, "error: Cannot create thread # %d\n", i);
              break;
            }
//            if (pthread_create(&threads[i+1], NULL, threadSqMean, (void*)&stArgs) != 0)
//            {
//              fprintf(stderr, "error: Cannot create thread # %d\n", i);
//              break;
//            }
//            if (pthread_create(&threads[i+2], NULL, threadPowSum, (void*)&stArgs) != 0)
//            {
//              fprintf(stderr, "error: Cannot create thread # %d\n", i);
//              break;
//            }

            pthread_join(threads[i],(void**)&moyenneUnPeu);/*
            pthread_join(threads[i+1],NULL);
            pthread_join(threads[i+2],NULL);*/

            printf("La moyenne vaut %f \n",*moyenneUnPeu);

            i++;
            j+=3;
        }

    }

    end = clock();

    //float endTime = time(NULL);
    //float myDuration = (endTime - iniTime) / nbIte;

    float myDurationClock = (double)(end - start) / nbIte / CLOCKS_PER_SEC;

    printf ("\n\nDuree moyenne sur %d iterations : %f secondes.\n\n", N, myDurationClock);

}



