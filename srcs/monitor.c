
#include "../headers/philosophers.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_shared_data	*shared_data;
	int philosopher_died;
	int index;
	
	philos = (t_philo *)arg;
	shared_data = philos->shared_data;
	philosopher_died = 0;
	while (1)
	{
		index = 0;
	    while (index < shared_data->num_philos)
	    {
	        if (philo_dead(philos, shared_data->time_to_die, index))
	        {
	            philosopher_died = 1;
	            break;
	        }
			index++;
	    }

	    if (philosopher_died || meals_finished(philos, shared_data))
	        break;
	}

	return (arg);
}

short int philo_dead(t_philo *philo, int time_to_die, int index)
{
    pthread_mutex_lock(philo[index].eat_mutex);
    if (get_current_time() - philo[index].last_meal >= time_to_die && !philo[index].eating)
    {
        pthread_mutex_unlock(philo[index].eat_mutex);
        print_message("died", &philo[index], philo[index].id);
        pthread_mutex_lock(philo[0].stop_flag_mutex);
        *philo->stop = 1;
        pthread_mutex_unlock(philo[0].stop_flag_mutex);
        return (1);
    }
    pthread_mutex_unlock(philo[index].eat_mutex);
    return (0);
}


short int	meals_finished(t_philo *philos, t_shared_data *shared_data)
{
	int	i;
	int	finished_eating;

	i = 0;
	finished_eating = 0;
	if (shared_data->num_meals == -1)
		return (0);
	while (i < shared_data->num_philos)
	{
		pthread_mutex_lock(philos[i].eat_mutex);
		if (philos[i].meals_eaten >= shared_data->num_meals)
			finished_eating++;
		pthread_mutex_unlock(philos[i].eat_mutex);
		i++;
	}
	if (finished_eating == philos[0].shared_data->num_philos)
	{
		pthread_mutex_lock(philos[0].stop_flag_mutex);
		*philos->stop = 1;
		pthread_mutex_unlock(philos[0].stop_flag_mutex);
		return (1);
	}
	return (0);
}
