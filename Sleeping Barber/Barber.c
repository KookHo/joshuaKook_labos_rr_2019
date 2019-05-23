#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

#define CHAIR 5
#define TRUE 1

sem_t customers;
sem_t barbers;
sem_t mutex;
int waiting = 0;

void* barber(void* arg);
void* customer(void* arg);
void cut_hair();
void customer_arrived();
void get_haircut();
void giveup_haircut();


int main(){
	sem_init(&customers, TRUE, 0);
	sem_init(&barbers, TRUE, 0);
	sem_init(&mutex, TRUE, 1);

	pthread_t id1, id2;

  //initialize the barber
	pthread_create(&id1, NULL, barber, NULL);

  //keeps generating clients
	while(TRUE){
		pthread_create(&id2, NULL, customer, NULL);
		sleep(1);
	}
	return 0;
}

//barber checks if there are customers
//if there's none, barber sleeps, otherwise,
//barber cuts a client's hair
void* barber(void* arg){
	while(TRUE){
		sem_wait(&customers);
		sem_wait(&mutex);
		waiting--;
		sem_post(&barbers);
		sem_post(&mutex);
		cut_hair();
	}
	pthread_exit(NULL);
}

//custumer arrives and checks to see if there's any
//free seat. If there's free seats, clients takes a seat
//and wait for barber to cut his hair, if there's not,
//client leaves
void* customer(void* arg){
  printf("A client has arrived\n");
	sem_wait(&mutex);
  //check to see if there's any free chair
	if(waiting < CHAIR){
		customer_arrived();
		waiting++;
		sem_post(&customers);
		sem_post(&mutex);
		sem_wait(&barbers);
		get_haircut();
	}else{
    //leave if there's no chair
		sem_post(&mutex);
		giveup_haircut();
	}
	pthread_exit(NULL);
}

void cut_hair(){
	printf("Barber is cutting a client's hair\n");
	sleep(3);
}

void customer_arrived(){
	printf("Client takes a seat\n");
}
void get_haircut(){
	printf("A client is getting his hair cut\n");
}

void giveup_haircut(){
	printf("No free chairs, client leaves\n");

}