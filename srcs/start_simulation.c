#include "../headers/philosophers.h"

int	start_simulation(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor, program->philos) != 0)
		destroy_all("Thread creation error", program, program->philos, forks, program->philos->shared_data->num_philos); //fix destroy all
	i = 0;
	while (i < program->philos[0].shared_data->num_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &life_cycle,
				&program->philos[i]) != 0)
			destroy_all("Thread creation error", program, program->philos, forks, program->philos->shared_data->num_philos);
		i++;
	}
	i = 0;
	if (pthread_join(observer, NULL) != 0)
		destroy_all("Thread join error", program, program->philos, forks, program->philos->shared_data->num_philos);
	while (i < program->philos[0].shared_data->num_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL) != 0)
			destroy_all("Thread join error", program, program->philos, forks, program->philos->shared_data->num_philos);
		i++;
	}
	return (0);
}