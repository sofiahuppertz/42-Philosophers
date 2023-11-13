#include "../headers/philosophers.h"

#include <unistd.h>

int init_program(t_program *program, t_philo *philos)
{
    program->dead_flag = 0;
    program->philos = philos;

    if (pthread_mutex_init(&program->write_lock, NULL) != 0 ||
        pthread_mutex_init(&program->dead_lock, NULL) != 0 ||
        pthread_mutex_init(&program->meal_lock, NULL) != 0) {
        write(2, "Error: Failed to initialize mutex\n", 34);
        return 0;
    }
    return 1;
}

int init_forks(pthread_mutex_t *forks, int philo_num) 
{
    int i = 0;
    int init_result;

    while (i < philo_num) {
        init_result = pthread_mutex_init(&forks[i], NULL);
        if (init_result != 0) 
        {
            write(2, "Error: Failed to initialize mutex\n", 35);
            return 0;
        }
        i++;
    }
    return 1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		t_shared_data *shared_data)
{
	int	i;

	i = 0;
	while (i < shared_data->num_philos)
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
        philos[i].shared_data = shared_data;
        philos[i].start_time = get_current_time();
		philos[i].last_meal = get_current_time();
		philos[i].print_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + shared_data->num_philos - 1) % shared_data->num_philos]; // this is the line that was changed (if-else before)
		i++;
	}
}
