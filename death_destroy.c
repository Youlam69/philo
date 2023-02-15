#include "philo.h"

void	dstroy_m(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_unlock(&data->hold);
	pthread_mutex_destroy(&data->hold);
	free(data->tabphilo);
	data->tabphilo = NULL;
	pthread_mutex_destroy(&(data->msg));
	while (++i < data->nof)
    {
	    pthread_mutex_unlock(&data->fork[i]);
		pthread_mutex_destroy(&data->fork[i]);
    }
	free(data->fork);
}

void	*die_conditon(void *death)
{
	t_ph *tph;

	tph = (t_ph *)death;
	while (1)
	{
		if((tph->last_eat - tph->tdata->start) >= tph->tdata->ttd)
		{
			pthread_mutex_lock(&tph->tdata->msg);
			tph->tdata->die++;
			printf("mat bjou3\n");
			pthread_mutex_unlock(&tph->tdata->hold);

			break;
		}
		if(tph->tdata->all_eat >= tph->tdata->nof)
		{
			pthread_mutex_lock(&tph->tdata->msg);
			tph->tdata->die++;
			printf("salina 7it kolchy kla\n");
			pthread_mutex_unlock(&tph->tdata->hold);
			break;
		}
	}
	return (NULL);
}