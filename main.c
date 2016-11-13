#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define REST_LOOP 1000000000
#define WORKOUT_LOOP 500000000

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
char command[5];

//Funktionen

void PUT_WEIGHTS(WEIGHTS weight){
	depot.five_kg += weight.five_kg;
	depot.three_kg += weight.three_kg;
	depot.two_kg += weight.two_kg;
}

WEIGHTS GET_WEIGHTS(int value ){

	WEIGHTS output;
	WEIGHTS depot_clone;
	int* slot;
	int* mySlot;
	int slotWeight;
	int result;
	int modulo;
	int weight;
	int sum;
	

	



	

	int k;
	while(k<3 && sum!=value){

		output.five_kg = 0;
		output.three_kg = 0;
		output.two_kg = 0;

		weight = value;
		depot_clone = depot;

		if(k==1){
			depot_clone.five_kg=0;
		}

		if(k==2){
			depot_clone.five_kg=0;
			depot_clone.three_kg=0;
		}

		int i;
		for (i = 0; i < 3; i++)
		{
			if(i==0){
				slot = &depot_clone.five_kg;
				slotWeight=5;
				mySlot = &output.five_kg;
			}

			if(i==1){
				slot = &depot_clone.three_kg;
				slotWeight=3;
				mySlot = &output.three_kg;
			}

			if(i==2){
				slot = &depot_clone.two_kg;
				slotWeight=2;
				mySlot = &output.two_kg;
			}

			if(*slot!=0){

				result = weight/slotWeight;

				while(result>=1){

					modulo = weight%slotWeight;

					if(result!=0 && weight-slotWeight*result!=1 
						&& weight>=slotWeight && *slot-result>=0){

						*mySlot = result;
						*slot = *slot-result;
					
						if(modulo!=0){
							weight = weight-slotWeight*result;
						} 
						else{
							//finish
							weight=0;
							sum = output.five_kg*5+output.three_kg*3+output.two_kg*2;
							break;
						}
					}
					else{
						result--;
					}
				}
			}
		}
		k++;
	}

	if(sum==value){
		depot.five_kg  -= output.five_kg;
		depot.three_kg -= output.three_kg;
		depot.two_kg   -= output.two_kg;
	}
	else{
		output.five_kg = 0;
		output.three_kg = 0;
		output.two_kg = 0;
	}

	return output;
}

// Philosophen - Threadfunktion
void* philosoph(void* value) {

	philo_zaehler++;
	
	int num = philo_zaehler;
	WEIGHTS myWeights;
	int i;
	int loop = 1;

	while(strcmp(command, "q") != 0){
		myWeights = GET_WEIGHTS( (int) value );

		printf("\nIch bin Philosoph Nr.: %d\n Ich traniere mit %d kg (%d, %d, %d)\n", 
			num, (int) value, myWeights.five_kg, myWeights.three_kg, myWeights.two_kg);
		printf("-->>Das Depot hat noch: (%d, %d, %d)\n", depot.five_kg, depot.three_kg, depot.two_kg);


		for(i=0; i<WORKOUT_LOOP; i++){

		}

		PUT_WEIGHTS(myWeights);
		printf("\n(%d)Das Depot hat wieder: (%d, %d, %d)\n\n", num, depot.five_kg, depot.three_kg, depot.two_kg);
		for(i=0; i<REST_LOOP; i++){

		}

	}

	pthread_exit(NULL);

   return NULL;
}


int main() {
   
	// Gewichtespeicher
   depot.two_kg = 4;
   depot.three_kg = 4;
   depot.five_kg = 5;

   int run = 1;

   // printf("philosoph: (%d, %d, %d)\n", myWeights.five_kg, myWeights.three_kg, myWeights.two_kg);
   // printf("depot: (%d, %d, %d)\n\n", depot.five_kg, depot.three_kg, depot.two_kg);

   // PUT_WEIGHTS( myWeights );

   // printf("philosoph: (%d, %d, %d)\n", myWeights.five_kg, myWeights.three_kg, myWeights.two_kg);
   // printf("depot: (%d, %d, %d)\n\n", depot.five_kg, depot.three_kg, depot.two_kg);


   pthread_t p1, p2, p3, p4, p5;

   //starte Threads
   pthread_create(&p1, NULL, philosoph, 6);
   pthread_create(&p2, NULL, philosoph, 8);
   pthread_create(&p3, NULL, philosoph, 12);
   pthread_create(&p4, NULL, philosoph, 12);
   pthread_create(&p5, NULL, philosoph, 14);


   while(run){
 		fgets(command, 255, stdin);
 		//delete new line from input
 		int l = strlen(command);
 		command[l-1] = '\0';
 		
 		if(strcmp(command, "q") == 0 ){
 			run = 0;
 			printf("enter\n");
 		}

 		printf("Befehl: \"%s\" \n", command);
   }

   printf("Programm Ende\n");

   // warte auf Threads
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);

   
   pthread_join(p3, NULL);
   pthread_join(p4, NULL);
   pthread_join(p5, NULL);

   printf("depot: (%d, %d, %d)\n\n", depot.five_kg, depot.three_kg, depot.two_kg);

   return 0;
}