#include "../headers/philosophers.h"

#include <unistd.h>

int init_program(t_program *program, t_philo *philos)
{
    program->stop_program = 0;
    program->philos = philos;

    if (pthread_mutex_init(&program->write_lock, NULL) != 0 ||
        pthread_mutex_init(&program->stop_flag_mutex, NULL) != 0 ||
        pthread_mutex_init(&program->eat_mutex, NULL) != 0) {
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
		philos[i].print_mutex = &program->write_lock;
		philos[i].stop_flag_mutex = &program->stop_flag_mutex;
		philos[i].eat_mutex = &program->eat_mutex;
		philos[i].stop = &program->stop_program;
		philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + shared_data->num_philos - 1) % shared_data->num_philos]; // this is the line that was changed (if-else before)
		i++;
	}
}
