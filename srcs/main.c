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
    if (!init_forks(&forks, t))
        return (1);
    if (!init_philosophers(&philo, forks, t))
        return (1);
    if (!init_threads(&thread, philo, t, forks))
        return (1);
    end_simulation(philo, t, forks, thread);
    return (0);
}
