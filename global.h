#include <pthread.h>
#include <semaphore.h>

#define REST_LOOP 1000000000
#define WORKOUT_LOOP 50000000

//Strukturen & Typdefinitionen
struct wgts{
	int two_kg;
	int three_kg;
	int five_kg;
};
typedef struct wgts WEIGHTS;

struct philo
{
	int id;
	int weight_for_training;
	char name[10]; 
	char mode[5];
	char status[5];
	WEIGHTS *weights;
	sem_t *sem;
};
typedef struct philo PHILOSOPH;

//Globale Variablen
int philo_zaehler;
WEIGHTS depot;
char command[5];
pthread_mutex_t mutex;
pthread_cond_t condition;
PHILOSOPH philos[5];
int weights_avialable;

void get__status();
int getThreadId();