#include "philo.h"

void	rotine(t_ph *tph)
{
	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID - 1]);
	print_msg("has taken a fork", tph, 1);
	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID % tph->tdata->nof]);
	print_msg("has taken a fork", tph, 2);
	tph->last_eat = get_time();
	usleep(tph->tdata->tte * 1000);
	pthread_mutex_unlock(&tph->tdata->fork[tph->p_ID - 1]);
	pthread_mutex_unlock(&tph->tdata->fork[tph->p_ID % tph->tdata->nof]);
	tph->nt_e++;
	if (tph->nt_e == tph->tdata->nofe)
		tph->tdata->all_eat++;
	print_msg("is sleeping", tph, 1);
	usleep(tph->tdata->tts * 1000);
	print_msg("is thinking", tph, 1);
}

void	*die_conditon(void *death)
{
	t_ph *tph;

	tph = (t_ph *)death;
	while (!tph->tdata->die)
	{
		if (get_time() - tph->last_eat >= tph->tdata->ttd + ((100 * (tph->p_ID - 1) / 1000)))
		{
			pthread_mutex_lock(&tph->tdata->msg);
			print_msg("died", tph, 0);
			tph->tdata->die++;
		}
	}
	return (NULL);
}

void	*death_note(void *death)
{
	t_data *data;

	data = (t_data *)death;
	while (!data->die)
	{
		if(data->all_eat >= data->nof)
		{
			pthread_mutex_lock(&data->msg);
			data->die++;
		}
	}
	return (NULL);
}

void	*work_p(void *p_tph)
{
	pthread_t die;

	t_ph *tph = (t_ph *)p_tph;
	if (pthread_create(&die, NULL, die_conditon, tph))
		return (NULL);
	while (!tph->tdata->die)
		rotine(tph);
	pthread_detach(die);
	return (NULL);
}


int start_thread(t_data *data)
{
	int			i;
	pthread_t	die;

	if (pthread_create(&die, NULL, death_note, data))
		return (1);
	i = -1;
	data->die = 0;
	data->all_eat = 0;
	while (++i < data->nof)
	{
		data->tph[i].p_ID = i + 1;
		data->tph[i].nt_e = 0;
		if (!i)
			data->start = get_time();
		// data->tph[i].last_eat = data->start;
		data->tph[i].last_eat = data->start;
		if (pthread_create(&data->tph[i].suqrat, NULL, work_p, &data->tph[i]))
			return (1);
		pthread_detach(data->tph[i].suqrat);
		usleep(50);
	}
	pthread_join(die, NULL);
	return (0);
}
