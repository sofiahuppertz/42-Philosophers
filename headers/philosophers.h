#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>


typedef struct s_shared_data
{	
    int			num_philos;
    int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_meals;

} t_shared_data;

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	int			start_time;
	int			last_meal;
	int				*stop;
	t_shared_data   *shared_data;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*stop_flag_mutex;
	pthread_mutex_t	*eat_mutex;
}					t_philo;

typedef struct s_program
{
	int				stop_program;
	pthread_mutex_t	stop_flag_mutex;
	pthread_mutex_t	eat_mutex;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void	destroy_all(char *str, t_program *program, t_philo *philos, pthread_mutex_t *forks, int total);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		t_shared_data *shared_data);
void	*life_cycle(void *arg);
void	*monitor(void *arg);
void	print_message(char *str, t_philo *philo, int id);
void	think(t_philo *philo);

int	ft_atoi(char *str);
int	ft_usleep(size_t milliseconds);
int	get_current_time(void);
int init_forks(pthread_mutex_t *forks, int philo_num);
int init_program(t_program *program, t_philo *philos);
int	main(int argc, char **argv);
int	start_simulation(t_program *program, pthread_mutex_t *forks);
int	valid_arguments(char **argv, t_shared_data *data);

short int	game_over(t_philo *philo);
short int	philo_dead(t_philo *philos, int time_to_die, int index);
short int is_digit(char *str);
short int	meals_finished(t_philo *philos, t_shared_data *shared_data);

#endif