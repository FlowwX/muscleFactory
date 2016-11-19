#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

#include <global.h>
#include <muscleFactory.h>
#include <philosoph.h>


void workout(PHILOSOPH *p);
void rest(PHILOSOPH *p);
void read_input(PHILOSOPH *p);



// Philosophen - Threadfunktion
void* philosoph(void* value) {

	PHILOSOPH *p = (PHILOSOPH*) value; 

	while(strcmp(command, "q") != 0){

		//enter critical region
		pthread_mutex_lock(&mutex);
		strcpy(p->status, "G");
		strcpy(p->mode, "b");
		get__status();
		while(!GET_WEIGHTS( p )){
			pthread_cond_wait(&condition, &mutex);
		}
		strcpy(p->mode, "n");
		pthread_mutex_unlock(&mutex);


		strcpy(p->status, "W");
		get__status();
		workout(p);

		pthread_cond_signal(&condition);
		
		//leave critical region	

		strcpy(p->status, "P");
		get__status();
		PUT_WEIGHTS(p);

		strcpy(p->status, "R");
		get__status();
		rest(p);
		get__status();

	}

	pthread_exit(NULL);

   return NULL;
}

void workout(PHILOSOPH *p){
	int i;
	int pid=-1;
	for(i=0; i<WORKOUT_LOOP; i++){
		read_input(p);

		if(strstr(command, "p" )){
			int id = getThreadId();
			if(id>=-1){
				if(id==p->id){
					pid=id;
					break;
				}
			}
		}
	}
	if(pid!=-1){
			printf("(%d)jump to end of workout\n", pid);
	}
}

void rest(PHILOSOPH *p){
	int i;
	int pid=-1;
	for(i=0; i<REST_LOOP; i++){
		read_input(p);

		if(strstr(command, "p" )){
			int id = getThreadId();
			if(id>=-1){
				if(id==p->id){
					pid=id;
					break;
				}
			}
		}
	}
	if(pid!=-1){
			printf("(%d)jump to end of rest\n", pid);
	}

}

void read_input(PHILOSOPH *p){
	if(strstr(command, "q" )){
		strcpy(p->mode, "q");
	}

	if(strstr(command, "b" )){
		int id = getThreadId();
		if(id>=-1){
			if(id==p->id){
				strcpy(p->mode, "b");
				get__status();
				sem_wait(p->sem);
			}
		}
	}
}
