#include "../philosophers.h"

void end_simulation(philo_t **philo, data_t *t, fork_t *forks, pthread_t *thread)
{
    int all_terminated = 0;
    int i;

    while(!all_terminated)
    {
        pthread_mutex_lock(&t->end_mutex);
        if (t->terminated == t->philo_total)
            all_terminated = 1;
        pthread_mutex_unlock(&t->end_mutex);
        pthread_mutex_unlock(&t->end_mutex);
    }
    i = 0;
    while (i < t->philo_total)
    {
        pthread_join(thread[i], NULL);
        i += 1;
    }
    free_memory(philo, forks, t, NULL, 0);
    
}

void free_memory(philo_t **philo, fork_t *forks, data_t *t, char *str, int error) {
    
    int i;
    int total;

    if(t)
        total = t->philo_total;
    if (philo)
    {
        i = 0;
        while (i < total && *philo)
        {
            if (philo[i])
            {
                free(philo[i]);
            }
            i += 1;
        }
        free(philo);
    }   
    if (t)
    {
        pthread_mutex_destroy(&t->print_mutex);
        pthread_mutex_destroy(&t->end_mutex);
        free(t);
    }
    if (forks)
    {
        i = 0;
        while (i < total)
        {
            pthread_mutex_destroy(&forks[i].mutex);
            i += 1;
        }
        free(forks);
    }
    if (str)
        printf("%s", str);
    if (error)
        exit(1);
    return;
}