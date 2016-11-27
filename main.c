#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include <global.h>
#include <philosoph.h>
#include <semaphore.h>



int main() {

	strcpy(command, "-");   

   int i;
   for(i=0; i<5; i++){
	    
	   	PHILOSOPH p = {i,0,"","n","G", malloc(sizeof(WEIGHTS)), malloc(sizeof(sem_t))};

	   	philos[i] = p; 

	   	philos[i].weights->five_kg = 0;
	   	philos[i].weights->three_kg = 0;
	   	philos[i].weights->two_kg = 0;
   }	

   strcpy( philos[0].name, "Anna");
   philos[0].weight_for_training = 6;
   strcpy( philos[1].name, "Bernd");
   philos[1].weight_for_training = 8;
   strcpy( philos[2].name, "Clara");
   philos[2].weight_for_training = 12;
   strcpy( philos[3].name, "Dirk");
   philos[3].weight_for_training = 12;
   strcpy( philos[4].name, "Emma");
   philos[4].weight_for_training = 14;




	// Gewichtespeicher
   depot = (WEIGHTS){4,4,5};

   int run = 1;

   pthread_t p1, p2, p3, p4, p5;

   //starte Threads
   pthread_create(&p1, NULL, philosoph, (void*) &philos[0]);
   pthread_create(&p2, NULL, philosoph, (void*) &philos[1]);
   pthread_create(&p3, NULL, philosoph, (void*) &philos[2]);
   pthread_create(&p4, NULL, philosoph, (void*) &philos[3]);
   pthread_create(&p5, NULL, philosoph, (void*) &philos[4]);



   while(run){
 		fgets(command, 255, stdin);
 		//delete new line from input
 		int l = strlen(command);
 		command[l-1] = '\0';
 		
 		if(strcmp(command, "q") == 0 ){
 			run = 0;
			//unblock all semaphores
			int i;
			for(i=0; i<5; i++)
			{
				sem_post(philos[i].sem);
			}
 		}

		if(strstr(command, "u" )){
			int id = getThreadId();
			if(id>=-1){
				strcpy(philos[id].mode, "b");
				get__status();
				sem_post(philos[id].sem);
				printf("\n\n Unblock Thread Nr.: %d\n\n", id);
			}
		}
   }

   printf("Mainloop ends\n");
   printf("Wait for threads\n");

   // warte auf Threads
   pthread_join(p1, NULL);
   pthread_join(p2, NULL);
   pthread_join(p3, NULL);
   pthread_join(p4, NULL);
   pthread_join(p5, NULL);

	printf("Last status:\n");
  	get__status();

   return 0;
}

void get__status(){
	int i;
	for(i=0; i<5; i++){
		printf("%d(%d)%s:%s(%d,%d,%d) - ", philos[i].id, philos[i].weight_for_training,
		 	philos[i].mode, philos[i].status,
		 	philos[i].weights->two_kg, philos[i].weights->three_kg, philos[i].weights->five_kg);
	}
	printf("Supply:(%d,%d,%d)\n", depot.two_kg, depot.three_kg, depot.five_kg);
}



int getThreadId(){
	char * cp = &command;

	if(isdigit(*cp)){
		return (int) strtol(cp, &cp, 10);
	}

	return -1;
}
