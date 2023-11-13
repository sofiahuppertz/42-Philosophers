 
#include "../headers/philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_message("has taken a fork", philo, philo->id);
	if (philo->shared_data->num_philos == 1)
	{
		ft_usleep(philo->shared_data->time_to_die);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(philo->left_fork);
	print_message("has taken a fork", philo, philo->id);
	philo->eating = 1;
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->eat_mutex);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->eat_mutex);
	ft_usleep(philo->shared_data->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->shared_data->time_to_sleep);
}