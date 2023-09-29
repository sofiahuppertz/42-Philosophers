#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>


typedef struct fork_s {
    int id;
    pthread_mutex_t mutex;
} fork_t;

typedef struct data_s {
    int philo_total;
    int time_to_die; //If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
    int someone_died;
    struct timeval start_of_simulation;
} data_t;

typedef struct philo_s {
    int id;
    int eaten_meals;
    struct timeval last_meal;
    data_t *t;
    fork_t *left;
    fork_t *right;
} philo_t;


int    check_args(int argc, char *argv[]);
int init_data(data_t **data, char *argv[]);
int init_forks(fork_t **forks, data_t *t);
int init_philosophers(philo_t ***philo, fork_t *forks, data_t *t);
int init_threads(pthread_t **thread, philo_t **philo, data_t *t, fork_t *forks) ;
int str_to_int(char *str);
int valid_number(char *str);

void	*my_calloc(size_t elements, size_t size);
void *philo_lifestyle (void *arg);

void free_memory(philo_t **philo, fork_t *forks, data_t *t);

#endif