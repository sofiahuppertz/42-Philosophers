#include "../philosophers.h"

int main(int argc, char *argv[]) {
    data_t *t;
    fork_t *forks;
    philo_t *philo;
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
    if (!init_threads(&thread, philo))
        return (1);
    return (0);

}

void free_memory(philo_t *philo, fork_t *forks, data_t *t) {
    
    int i;
    int total;

    total = t->philo_num;

    if (philo)
        free(philo);
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