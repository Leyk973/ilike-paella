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

    double* res;
    res = (double*)malloc(sizeof(double));
    *res = 0;

    float temp;

    for (size_t i = 1; i <= struData->tabSize; ++i)
    {
        temp = struData->ptrTab[i];
        *res += pow(temp,2);
    }

    *res = *res/struData->tabSize;
    *res = sqrt(*res);

    pthread_exit((void*)res);

    return NULL;

}

/*thread function 3 : 3powSum*/
void * threadPowSum (void* arg)
{
    datatata *struData = (datatata*)arg;

    double* res;
    res = (double*)malloc(sizeof(double));
    *res = 0;

    float temp;

    for (size_t i = 1; i <= struData->tabSize; ++i)
    {
        temp = struData->ptrTab[i];
        *res += pow(temp,3);
    }

    pthread_exit((void*)res);

    return NULL;

}



int main(void)
{
    FILE *f = fopen("tempsEnParallele.txt","w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }




    // nombre d'itérations
    size_t nbIte=10;

    int N = 20;

    while (N <= 300)
    {
        //    printf("Valeur de N ? : ");
        //    scanf("%d",&N);

            //float iniTime = time(NULL);

            clock_t start, end;

            start = clock();



            for (size_t y = 0 ; y < nbIte ; ++y)
            {
                srand(time(NULL));


                int i = 1;
                int j = i;
                float T [N];

                // trois threads par t
                int NB_THREADS = 3*N;
                pthread_t threads [NB_THREADS];

                //argument pour threads
                datatata stArgs;
                stArgs.ptrTab=T;
                stArgs.tabSize=i;


                double* moyenne;
                double* moyQuad;
                double* somCube;


                while (i <= N)
                {

                    T[i] = rand();

                    stArgs.ptrTab=T;
                    stArgs.tabSize=i;

                    if (pthread_create(&threads[j], NULL, threadMean, (void*)&stArgs) != 0)
                    {
                      fprintf(stderr, "error: Cannot create thread # %d\n", i);
                      break;
                    }
                    if (pthread_create(&threads[j+1], NULL, threadSqMean, (void*)&stArgs) != 0)
                    {
                      fprintf(stderr, "error: Cannot create thread # %d\n", i);
                      break;
                    }
                    if (pthread_create(&threads[j+2], NULL, threadPowSum, (void*)&stArgs) != 0)
                    {
                      fprintf(stderr, "error: Cannot create thread # %d\n", i);
                      break;
                    }

                    pthread_join(threads[j],(void**)&moyenne);
                    pthread_join(threads[j+1],(void**)&moyQuad);
                    pthread_join(threads[j+2],(void**)&somCube);

                    printf("La moyenne vaut %f \n",*moyenne);
                    printf("La moyenne quadratique vaut %f \n",*moyQuad);
                    printf("La somme des cubes vaut %f \n",*somCube);

                    i++;
                    j+=3;
                }


                //printf("-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_\n");


            }

            end = clock();

            float myDurationClock = (double)(end - start) / nbIte / CLOCKS_PER_SEC;

            fprintf (f,"\n\nDuree moyenne sur %d iterations : %f secondes.\n\n", N, myDurationClock);

            N+=20;

    }
    fclose(f);

}



