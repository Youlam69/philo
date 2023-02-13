#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 44
#define NUM_FORKS 44

void *philosopher(void *id);

pthread_mutex_t forks[NUM_FORKS];

int main(int argc, char **argv) {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int i;

    for (i = 0; i < NUM_FORKS; i++) {
        pthread_mutex_init(&forks[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)i);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (i = 0; i < NUM_FORKS; i++) {
        pthread_mutex_destroy(&forks[i]);
    }

    return 0;
}

void *philosopher(void *num) {
    int id = (int)num;
    int leftFork = id;
    int rightFork = (id + 1) % NUM_FORKS;

    while (1) {
        printf("Philosopher %d is thinking\n", id);
        sleep(1);

        printf("Philosopher %d is hungry\n", id);
        pthread_mutex_lock(&forks[leftFork]);
        pthread_mutex_lock(&forks[rightFork]);
        printf("Philosopher %d is eating\n", id);
        sleep(1);
        pthread_mutex_unlock(&forks[leftFork]);
        pthread_mutex_unlock(&forks[rightFork]);
    }
}

