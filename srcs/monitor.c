
#include "../headers/philosophers.h"

void *monitor(void *arg)
{
    t_philo *philosophers = (t_philo *)arg;
    t_shared_data *shared_data = philosophers->shared_data;

    while (1)
    {
        for (int index = 0; index < shared_data->num_philos; ++index)
        {
            if (is_dead(&philosophers[index], shared_data->time_to_die))
                break;
        }

        if (meals_done(philosophers, shared_data))
            break;
    }
    return arg;
}

short int is_dead(t_philo *philosopher, int time_to_die)
{
	short int dead;

	dead = 0;
    pthread_mutex_lock(philosopher->meal_lock);
	if (get_current_time() - philosopher->last_meal >= time_to_die && philosopher->eating == 0)
    	dead = 1;
    pthread_mutex_unlock(philosopher->meal_lock);
    return dead;
}

short int meals_done(t_philo *philosophers, t_shared_data *shared_data)
{
    int finished_eating = 0;
	int philo_idx;

	philo_idx = 0;
    while (philo_idx++ < shared_data->num_philos)
    {
        pthread_mutex_lock(philosophers[philo_idx].meal_lock);
        if (philosophers[philo_idx].meals_eaten >= shared_data->num_meals)
        {
            finished_eating++;
        }
        pthread_mutex_unlock(philosophers[philo_idx].meal_lock);
    }
    if (finished_eating == shared_data->num_philos)
		return 1;
	return (0);
}



