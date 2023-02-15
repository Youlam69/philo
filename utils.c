#include "philo.h"

void	dstroy_m(t_data *data)
{
	int	i;

	i = -1;
	free(data->tph);
	data->tph = NULL;
	pthread_mutex_destroy(&(data->msg));
	while (++i < data->nof)
		pthread_mutex_destroy(&data->fork[i]);
	free(data->fork);
}

void	print_msg(char *tab, t_ph *tph, int ref)
{
	if (ref)
	{
		pthread_mutex_lock(&tph->tdata->msg);
		if (ref == 2)
		{
			printf("at %ld Philosopher : %d is %s\n", get_time() - tph->tdata->start, tph->p_ID, tab);
			printf("at %ld Philosopher : %d is %s\n", get_time() - tph->tdata->start, tph->p_ID, "eating");
		}
		else
			printf("at %ld Philosopher : %d is %s\n", get_time() - tph->tdata->start, tph->p_ID, tab);
		pthread_mutex_unlock(&tph->tdata->msg);
	}
	else
		printf("at %ld Philosopher : %d is %s\n", get_time() - tph->tdata->start, tph->p_ID, tab);	
}

long int	get_time(void)
{
	struct timeval	t_v;
	long int		t_ms;

	gettimeofday(&t_v, NULL);
	t_ms = ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
	return (t_ms);
}