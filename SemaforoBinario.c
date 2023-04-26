/* SPIEGAZIONE */

// phtread_mutex_t semaforo; //nomina variabile
/* IN QUESTO MODO IL SEMAFORO VIENE SETTATO OCCUPATO(DI DEAFAULT E' LIBERO)*/
// staticamente--> phtread_mutex_t semaforo = PTHREAD_MUTEX_INITIALIZER; //semaforo parte dallo stato occupato
// dinamicamente--> pthread_mutex_init (pthread_mutex_t *semaforo, pthread_mutex_attr * attributi) 
// pthread_mutex_init(&bufferVuoto,NULL); --> inizializza semaforo libero
// int pthread_mutex_lock (pthread_mutex_t * semaforo) //sospende il semaforo
// int pthread_mutex_unlock(pthread_mutex_t * semaforo) // setta il semaforo a 1 (verde)

/*CODICE */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define TANTI1 30
#define TANTI2 20

int condivisa = 0; // variabile condivisa da main e thread
pthread_mutex_t mutex; // definizione semaforo

void *cod_thread(void *arg){ // funzione che viene eseguita dal thread
	int x,dato;
	for(x=0;x<TANTI1;x++){
		pthread_mutex_lock(&mutex); // entra nella sezione critica
		dato = condivisa; // aggiorna la variabile
		dato++; // copiando prima variabile locale
		condivisa = dato; // solo per ralentare l'esecuzione
		printf(".");  // il punto indica quando l'algoritmo è nel thread 
		pthread_mutex_unlock(&mutex); // esce dalla sezione critica
	}
}
int main(void) {
	pthread_t tid1;
	int x,err;
	pthread_mutex_init (&mutex,NULL); // semaforo inizializzato a verde
	if((err = pthread_create(&tid1,NULL,cod_thread,NULL)) != 0){
		printf("errore nella creazione thread: %d\n",strerror(err));
		exit(1);
	}
	for(x=0;x<TANTI2; x++){
		pthread_mutex_lock(&mutex); // entra nella sezione critica
		condivisa++;
		printf("o"); // la o indica quando l'algoritmo è nel main 
		pthread_mutex_unlock(&mutex); // esce della sezione critica
	}
	if(pthread_join(tid1,NULL)){
		printf("errore:%d\n",strerror(err));
		exit(1);
	}
	printf("\nVariabile condivisa uguale a: %d\n",condivisa);
	exit(0);
}
