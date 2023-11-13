
#include "../headers/philosophers.h"

/*

short int is_dead(t_philo *philosopher, int time_to_die)
{
    pthread_mutex_lock(philosopher->meal_lock);
    short int dead = ((get_current_time() - philosopher->last_meal >= time_to_die) && (philosopher->eating == 0)) ? 1 : 0;
    pthread_mutex_unlock(philosopher->meal_lock);
    return dead;
}

short int meals_done(t_philo *philosophers, t_shared_data *shared_data)
{
    int finished_eating = 0;
    for (int index = 0; index < shared_data->num_philos; ++index)
    {
        pthread_mutex_lock(philosophers[index].meal_lock);
        if (philosophers[index].meals_eaten >= shared_data->num_meals)
        {
            finished_eating++;
        }
        pthread_mutex_unlock(philosophers[index].meal_lock);
    }
    return (finished_eating == shared_data->num_philos) ? 1 : 0;
}

void *monitor(void *arg)
{
    t_philo *philosophers = (t_philo *)arg;
    t_shared_data *shared_data = philosophers->shared_data;

    while (1)
    {
        for (int index = 0; index < shared_data->num_philos; ++index)
        {
            if (is_dead(&philosophers[index], shared_data->time_to_die))
            {
                // Handle philosopher death
                break;
            }
        }

        if (meals_done(philosophers, shared_data))
        {
            // Handle all meals finished
            break;
        }
    }
    return arg;
}

*/


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

	    if (philosopher_died || meals__ok(philos, shared_data))
	        break;
	}

	return (arg);
}

int philo_dead(t_philo *philo, int time_to_die, int index)
{
    pthread_mutex_lock(philo[index].meal_lock);
    if (get_current_time() - philo[index].last_meal >= time_to_die && !philo[index].eating)
    {
        pthread_mutex_unlock(philo[index].meal_lock);
        print_message("died", &philo[index], philo[index].id);
        pthread_mutex_lock(philo[0].dead_lock);
        *philo->dead = 1;
        pthread_mutex_unlock(philo[0].dead_lock);
        return (1);
    }
    pthread_mutex_unlock(philo[index].meal_lock);
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



//FINISH ------

/*

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

*/