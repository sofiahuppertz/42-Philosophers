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
    t_shared_data   *shared_data;
	int				*dead;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

void	destroy_all(char *str, t_program *program, t_philo *philos, pthread_mutex_t *forks, int total);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
void	*life_cycle(void *arg);
void	*monitor(void *arg);
void	print_message(char *str, t_philo *philo, int id);
void	think(t_philo *philo);

int	check_dead(t_philo *philo);
int	ft_atoi(char *str);
int	get_current_time(void);
int init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		t_shared_data *shared_data);
int init_program(t_program *program, t_philo *philos);
int	is_digit(char *str);
int	main(int argc, char **argv);
int	check_if_all_ate(t_philo *philos, t_shared_data *shared_data);
int	check_if_dead(t_philo *philos, t_shared_data *shared_data);
int	philosopher_dead(t_philo *philo, int time_to_die);
int	start_simulation(t_program *program, pthread_mutex_t *forks);
int	valid_arguments(char **argv, t_shared_data *data);

#endif