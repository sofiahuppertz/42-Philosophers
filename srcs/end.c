#include "../headers/philosophers.h"

void	destroy_all(char *str, t_program *program, t_philo *philos, pthread_mutex_t *forks, int total)
{
	int	i;

	i = 0;
	if (str)
        printf("Error: %s\n", str);
	pthread_mutex_destroy(&program->write_lock);
	pthread_mutex_destroy(&program->eat_mutex);
	pthread_mutex_destroy(&program->stop_flag_mutex);
	while (i < total)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
    free(forks);
    if (philos)
        free(philos);
}
