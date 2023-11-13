
#include "../headers/philosophers.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_shared_data	*shared_data;

	philos = (t_philo *)arg;
	shared_data = philos->shared_data;
	while (1)
	{
		if (philo_dead(philos, shared_data->time_to_die, shared_data->num_philos))
			break ;
		if (meals__ok(philos, shared_data))
			break ;
	}
	return (arg);
}

int	philosopher_dead(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die
		&& philo->eating == 0)
		return (pthread_mutex_unlock(philo->meal_lock), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	philo_dead(t_philo *philos, int time_to_die, int total_philos)
{
	int	i;

	i = 0;
	while (i < total_philos)
	{
		if (philosopher_dead(&philos[i], time_to_die))
		{
			print_message("died", &philos[i], philos[i].id);
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	meals__ok(t_philo *philos, t_shared_data *shared_data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (shared_data->num_meals == -1)
		return (0);
	while (i < shared_data->num_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= shared_data->num_meals)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
		i++;
	}
	if (finished_eating == philos[0].shared_data->num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

