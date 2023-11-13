
#include "../headers/philosophers.h"

int	valid_arguments(char **argv, t_shared_data *data)
{
    int i;

    i = 1;
	while (i < 5)
    {
        if (!is_digit(argv[i]) || ft_atoi(argv[i]) <= 0)
            return (write(2, "Invalid argument\n", 17), 0);
        i++;
    }
	if (argv[5] && (!is_digit(argv[5]) || ft_atoi(argv[5]) < 0))
		return (write(2, "Invalid argument\n", 17 ), 0);
	data->num_philos = ft_atoi(argv[1]);
    data->time_to_die = ft_atoi(argv[2]);
    data->time_to_eat = ft_atoi(argv[3]);
    data->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        data->num_meals = ft_atoi(argv[5]);
    else
        data->num_meals = -1;
    return (1);
}

short int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}