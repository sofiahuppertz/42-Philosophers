#include "../philosophers.h"


int main(int argc, char *argv[]) {
    data_t *t;
    fork_t *forks;
    philo_t **philo;
    pthread_t *thread;

    t = NULL;
    forks = NULL;
    philo = NULL;
    thread = NULL; 

    if (!check_args(argc, argv))
        return (1);   
    if (!init_data(&t, argv))
        return (1);
    if (!init_forks(&forks, t))
        return (1);
    if (!init_philosophers(&philo, forks, t))
        return (1);
    int total = t->philo_total;
    if (!init_threads(&thread, philo, t, forks))
        return (1);
    for (int i = 0; i < total; i++)
    {
        pthread_join(thread[i], NULL);
    }
    return (0);
}


//how to free memory correctly with threads? INside of the threads...
void free_memory(philo_t **philo, fork_t *forks, data_t *t) {
    
    int i;
    int total;

    total = t->philo_total;

    if (philo && *philo)
    {
        i = 0;
        while (i < total)
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
}