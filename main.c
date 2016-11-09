#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Strukturen & Typdefinitionen
struct wgts{
	int two_kg;
	int three_kg;
	int five_kg;
};
typedef struct wgts WEIGHTS;

//Globale Variablen
int philo_zaehler;
WEIGHTS depot;


// Philosophen - Threadfunktion
void* philosoph(void* value) {

	philo_zaehler++;
	printf("Ich bin Philosoph Nr.: %d\n Ich traniere mit %d kg \n", philo_zaehler, (int) value);

   return NULL;
}

//Funktionen
WEIGHTS GET_WEIGHTS(int kg){

	WEIGHTS output;

	return output;
}



int main() {
   
	// Gewichtespeicher
   depot.two_kg = 4;
   depot.three_kg = 4;
   depot.five_kg = 5;

   pthread_t p1, p2, p3, p4, p5;

   //starte Threads
   pthread_create(&p1, NULL, philosoph, 6);
   pthread_create(&p2, NULL, philosoph, 8);
   pthread_create(&p3, NULL, philosoph, 12);
   pthread_create(&p4, NULL, philosoph, 12);
   pthread_create(&p5, NULL, philosoph, 14);

   //warte auf Threads
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(p3, NULL);
   pthread_join(p4, NULL);
   pthread_join(p5, NULL);

   return 0;
}