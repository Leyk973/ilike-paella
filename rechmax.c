#include <stdio.h>
#include <stdlib.h>
//#include <math.h> passer -lm en paramètre
//#include <pthread.h> passer -lpthread en paramètre

#define Taille = 100;

struct info
{
	int * T; int deb; //valeurs d'entrée pour le thread
	int max; int pos;
};

void* calcul(void* arg)
{
	int i;
	struct info * ptr;
	ptr = (struct info *)arg;
	ptr->max = ptr->T[ptr->deb];
	ptr->pos = ptr->deb;
	
	for (i=ptr->deb; i<=((ptr->deb)+50); i++)
	{
		if(ptr->T[i] > ptr->max) 
		{
			ptr->max = ptr->T[i];
			ptr->pos = i;
		}	
	}
	pthread_exit(NULL);
}

int main()
{	
	pthread_t t1,t2;
	int tab[100];
	int i;
	struct info st1, st2;
	//struct info * st1b, st2b;
	
	for (i=0;i<100;i++)
		tab[i]=random() % 501;
	tab[12]=2016;
	
	int* max1,max2,pos1,pos2;
	
	
	st1.T=tab; st1.deb=0;
	st2.T=tab; st2.deb=50;

	pthread_create(&t1,NULL,calcul,(void*)&st1); //un thread exécute une fonction
	pthread_create(&t2,NULL,calcul,(void*)&st2);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	
	
	
	
	if (st1.max >= st2.max)
		printf("Valeur max : %d a la position %d\n",st1.max,st1.pos);
	else
		printf("Valeur max : %d a la position %d\n",st2.max,st2.pos);
		

	//:D le début de la fortune, peut-être qu'en utilisant cette pièce on pourra vendre une machine très cher pour acheter de la nourriture pour mamie parce que là ça commence à faire 12 jours et c'est long sans manger quand même. Merci Père Noël. Bise. ZoubiLove <3 keurkeur
		
}
















