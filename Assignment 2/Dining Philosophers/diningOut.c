#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define EATING 0
#define HUNGRY 1
#define THINKING 2
#define LEFT (id + 4) % 5
#define RIGHT (id + 1) % 5

int phil_state[5];
int phil[5] = {0,1,2,3,4};

sem_t mutex;
sem_t forks[5];

void* philosopher(void* id);
void pickup_fork(int id);
void putdown_fork(int id);
void dinner_time(int id);


int main(){
    // thread for each philosopher
    int i;
    pthread_t thread_id[5];

    // initialie semaphores
    sem_init(&mutex, 0 ,1);

    for (i =0 ; i < 5; i++){
        sem_init(&forks[i], 0, 0);
    }

    // create philosophers
    for (i = 0; i < 5; i++){
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]);
        printf("Philosopher %d is thinking...\n", i +1);
    }

    for(i = 0; i < 5; i++){
        pthread_join(thread_id[i], NULL);
    }
}

// initialization of philosopher
void* philosopher(void* id){
    while (1){
        int* i = id;
        sleep(1);
        pickup_fork(*i);
        sleep(0);
        putdown_fork(*i);
    }
}

// philosopher picks up a fork
void pickup_fork(int id){
    sem_wait(&mutex);
    phil_state[id] = HUNGRY;
    printf("Philosopher %d is Hungry\n", id +1);

    // eats if able to
    dinner_time(id);

    sem_post(&mutex);

    // if unable to eat, wait
    sem_wait(&forks[id]);
    sleep(1);

}

// philosopher puts down a fork
void putdown_fork(int id){
    sem_wait(&mutex);

    phil_state[id] = THINKING;
    printf("Philosopher %d puts down fork %d and %d.\n", id +1, LEFT+1, id +1);
    printf("Philospher %d is thinking.\n", id +1);
    dinner_time(LEFT);
    dinner_time(RIGHT);

    sem_post(&mutex);

}

void dinner_time(int id){
    if (phil_state[id] == HUNGRY && phil_state[LEFT] != EATING && phil_state[RIGHT] != EATING){
        phil_state[id] = EATING;
        
        sleep(2);
        printf("Philosopher %d picks up forks %d and %d.\n", id +1, LEFT + 1, id +1);
        printf("Philosopher %d is eating.\n", id +1);

        sem_post(&forks[id]);
    }
}
