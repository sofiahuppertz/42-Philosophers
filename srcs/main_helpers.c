#include "../philosophers.h"

int    check_args(int argc, char *argv[]) {

    int i;
    if (argc != 5 && argc != 6) 
    {
        free_memory(NULL, NULL, NULL, "Error: wrong number of arguments\n", 1);
    }
        
    i = 1;
    while (i < argc)
    {
        if (!valid_number(argv[i]))
            return (0);
        i += 1;
    }
    return (1);

}

int init_data(data_t **t, char *argv[]) {
    
    *t = my_calloc(sizeof(data_t), 1);
    if (!(*t))
        free_memory(NULL, NULL, NULL, "data_t malloc error\n", 1);
    (*t)->philo_total = str_to_int(argv[1]);
    if ((*t)->philo_total == 0)
        free_memory(NULL, NULL, *t, "Invalid number of philosophers\n", 1);
    (*t)->time_to_die = str_to_int(argv[2]);
    (*t)->time_to_eat = str_to_int(argv[3]);
    (*t)->time_to_sleep = str_to_int(argv[4]);
    (*t)->terminated = 0;
    if (argv[5])
        (*t)->number_of_meals = str_to_int(argv[5]);
    else
        (*t)->number_of_meals = -1;
    memset(&(*t)->start_of_simulation, 0, sizeof(struct timeval));
    (*t)->someone_died = 0; 
    if (pthread_mutex_init(&(*t)->print_mutex, NULL))
        free_memory(NULL, NULL, *t, "pthread_mutex_init error\n", 1);
    if (pthread_mutex_init(&(*t)->end_mutex, NULL))
        free_memory(NULL, NULL, *t, "pthread_mutex_init error\n", 1);
    return (1);
}

int init_forks(fork_t **forks, data_t *t)
{
    int i;

    *forks = my_calloc(sizeof(fork_t), t->philo_total);
    if (!(*forks))
        free_memory(NULL, *forks, t, "fork_t malloc error\n", 1);        
    i = 0;
    while (i < t->philo_total)
    {
        (*forks)[i].id = i;
        if (pthread_mutex_init(&(*forks)[i].mutex, NULL))
            free_memory(NULL, *forks, t, "pthread_mutex_init error\n", 1);
        i += 1;
    }
    return (1);
}


int init_philosophers(philo_t ***philo, fork_t *forks, data_t *t) {
    
    int i;

    *philo = my_calloc(sizeof(philo_t *), t->philo_total);
    if (!(*philo))
        free_memory(*philo, forks, t, "philo_t malloc error\n", 1);
    i = 0;
    while (i < t->philo_total)
    {
        (*philo)[i] = my_calloc(sizeof(philo_t), 1);
        if (!(**philo))
            free_memory(*philo, forks, t, "philo_t malloc error\n", 1);
        (*philo)[i]->id = i;
        (*philo)[i]->eaten_meals = 0;
        memset(&(*philo)[i]->last_meal, 0, sizeof(struct timeval));
        (*philo)[i]->t = t;
        (*philo)[i]->left = &forks[i];
        (*philo)[i]->right = &forks[(i + 1) % t->philo_total];
        i += 1;
    }
    return (1);
}

int init_threads(pthread_t **thread, philo_t **philo, data_t *t, fork_t *forks) {
    int total;
    int i;

    i = 0;
    total = t->philo_total;
    *thread = my_calloc(sizeof(pthread_t), total);
    if (!(*thread))
        free_memory(philo, forks, t, "pthread_t malloc error\n", 1);
    gettimeofday(&t->start_of_simulation, NULL);
    printf("start of simulation: %ld\n", t->start_of_simulation.tv_sec); 
    while (i < total) {
        if (pthread_create(&(*thread)[i], NULL, &philo_lifestyle, philo[i]))
            free_memory(philo, forks, t, "pthread_create error\n", 1);
        i += 1;
    }
    return (1);

}