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
void critical_section(void);



// Philosophen - Threadfunktion
void* philosoph(void* value) {

	PHILOSOPH *p = (PHILOSOPH*) value; 

	while(strcmp(command, "q") != 0){

		//get weights
		strcpy(p->status, "G");
		strcpy(p->mode, "b");
		get__status();
		critical_section();

		strcpy(p->mode, "n");

		//workout
		strcpy(p->status, "W");
		get__status();
		workout(p);
		
		//put weights
		strcpy(p->status, "P");
		get__status();
		PUT_WEIGHTS(p);

		//rest
		strcpy(p->status, "R");
		get__status();
		rest(p);
		get__status();

	}

	pthread_exit(NULL);

   return NULL;
}

void critical_section(){
	pthread_mutex_lock(&mutex);
	
	while(!GET_WEIGHTS( p )){
		pthread_cond_wait(&condition, &mutex);
	}

	pthread_mutex_unlock(&mutex);	
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
	pthread_cond_signal(&condition);
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
					strcpy(command, "-");
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
