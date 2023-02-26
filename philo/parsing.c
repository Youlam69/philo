#include "philo.h"

void	init_prm(t_data *data)
{
	data->nof  = -1;
	data->ttd  = -1;
	data->tte = -1;
	data->tts = -1;
	data->nofe = -1;
}

int	data_p(t_data *data, int ac, char **av)
{
	init_prm(data);
	data->nof = my_atoi(av[1]);
	data->ttd = my_atoi(av[2]);
	data->tte = my_atoi(av[3]);
	data->tts = my_atoi(av[4]);
	if (data->nof <= 0 || data->ttd <= 0 || data->tte <= 0 || data->tts <= 0)
		return (-1);
	if (ac == 6)
	{
		data->nofe = my_atoi(av[5]);
		if (data->nofe < 0)
			return (-1);
		if (data->nofe == 0)
			return (-2);
	}
	return (0);
}

int parsing(int ac, char **av, t_data *data)
{
	int	ref;

	if (ac < 5 || ac > 6)
	{
		printf("Error : nbr of prms\n");
		return (1);
	}
	ref = data_p(data, ac, av);
	if (ref < 0)
	{
		if (ref == -1)
			printf("Error : not invalid arguments\n");
		return (1);
	}
	return (0);
}
