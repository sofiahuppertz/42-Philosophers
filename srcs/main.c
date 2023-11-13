#include "../headers/philosophers.h"

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			*philos;
    t_shared_data   shared_data;
	pthread_mutex_t	*forks;

	if (argc != 5 && argc != 6)
    {
        write(2, "Error: Invalid number of arguments\n", 35);
        return (1);
    }
	if (!valid_arguments(argv, &shared_data))
		return (1);
    philos = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
    if (!philos)
        return (write(2, "Error: malloc\n", 14), 1);
    forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
    if (!forks)
    {
        free(philos);
        return (write(2, "Error: malloc\n", 14), 1);
    }
	if (!init_program(&program, philos) || !init_forks(forks, shared_data.num_philos))
    {
        destroy_all("Failed to initialize program", &program, philos, forks, shared_data.num_philos);
        return (1);
    }
	init_forks(forks, shared_data.num_philos);
	init_philos(philos, &program, forks, &shared_data);
	start_simulation(&program, forks);
	destroy_all(NULL, &program, philos, forks, shared_data.num_philos);
	return (0);
}
