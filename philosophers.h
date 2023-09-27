#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>


typedef struct fork_s {
    int id;
    pthread_mutex_t mutex;
} fork_t;

typedef struct data_s {
    int philo_num;
    int time_to_die; //If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the sim- ulation, they die.
    int time_to_eat;
    int time_to_sleep;
    int number_of_meals;
} data_t;

typedef struct philo_s {
    int id;
    data_t *t;
    fork_t *left;
    fork_t *right;
} philo_t;


int    check_args(int argc, char *argv[]);
int init_data(data_t **data, char *argv[]);
int init_forks(fork_t **forks, data_t *t);
int init_philosophers(philo_t **philo, fork_t *forks, data_t *t);
int str_to_int(char *str);
int valid_number(char *str);

void	*my_calloc(size_t elements, size_t size)

void free_memory(philo_t *philo, fork_t *forks, data_t *t)
#endif