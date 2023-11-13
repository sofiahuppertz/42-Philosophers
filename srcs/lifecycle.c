#include "../headers/philosophers.h"

void	*life_cycle(void *arg)
{
	t_philo	*philo;

	short int res;
	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!(res = game_over(philo)))
	{
		eat(philo);
		dream(philo);;
		think(philo);
	}
	return (arg);
}

short int	game_over(t_philo *philo)
{
	pthread_mutex_lock(philo->stop_flag_mutex);
	if (*philo->stop == 1)
		return (pthread_mutex_unlock(philo->stop_flag_mutex), 1);
	pthread_mutex_unlock(philo->stop_flag_mutex);
	return (0);
}