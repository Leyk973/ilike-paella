#include <stdio.h>
#include <stdlib.h>
//#include <math.h> passer -lm en paramètre
//#include <pthread.h> passer -lpthread en paramètre

void* calcul(void * arg)
{
	int * deb=(int*)arg; //ou bien int deb = (int)&arg mais 
	//on travaille plus souvent avec des pointeurs dans les threads
	int i;
	double * som; 
	som = (double*)malloc(sizeof(double)); //malloc renvoie un truc non 
										//typé, donc on cast en double*
	*som = 0; 
	for(i=*deb;i<=100;i=i+2)
		*som=*som+sqrt(i);
	pthread_exit((void*)som); //retour de type void*
							  //som est de type double*
}

int main()
{
//la fonction main tourne sur un thread créé au lancement du programme
//on va créer deux threads de plus pour le calcul
	
	pthread_t t1, t2; //type identifiant de thread
	int i1=2, i2=1;
	double* som1;
	double* som2;
	//double res;
	
	pthread_create(&t1,NULL,calcul,(void*)&i1);
	pthread_create(&t2,NULL,calcul,(void*)&i2);
	
	pthread_join(t1,(void**)&som1); 
	//passage par adresse de som1 -> &som1 : double**
	pthread_join(t2,(void**)&som2);
	
	//res = *som1p + *som2p;
	
	printf("Somme : %lf\n",(*som1 + *som2));
	
}
