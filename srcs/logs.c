#include "../headers/philosophers.h"

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->print_mutex);
	time = get_current_time() - philo->start_time;
	if (!game_over(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->print_mutex);
}

int	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}