#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Globale Variablen
int philo_zaehler;


// Philosophen - Threadfunktion
void* philosoph(void* value) {

	philo_zaehler++;
	printf("Ich bin Philosoph Nr.: %d\n\n", philo_zaehler);

   return NULL;
}


int main() {
   
   pthread_t p1, p2, p3, p4, p5;

   //starte Threads
   pthread_create(&p1, NULL, philosoph, NULL);
   pthread_create(&p2, NULL, philosoph, NULL);
   pthread_create(&p3, NULL, philosoph, NULL);
   pthread_create(&p4, NULL, philosoph, NULL);
   pthread_create(&p5, NULL, philosoph, NULL);

   //warte auf Threads
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(p3, NULL);
   pthread_join(p4, NULL);
   pthread_join(p5, NULL);

   return 0;
}