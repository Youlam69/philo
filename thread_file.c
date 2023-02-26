#include "philo.h"

void	rotine(t_ph *tph)
{
	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID - 1]);
	print_msg("has taken a fork", tph, 1);
	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID % tph->tdata->nof]);
	print_msg("has taken a fork", tph, 2);

	pthread_mutex_lock(&tph->race_eat);
	tph->last_eat = get_time();
	pthread_mutex_unlock(&tph->race_eat);


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
	while (1)
	{
		pthread_mutex_lock(&tph->tdata->race_die);
		if (tph->tdata->die)
		{
			pthread_mutex_unlock(&tph->tdata->race_die);
			return NULL;
		}
		pthread_mutex_lock(&tph->race_eat);
		if (get_time() - tph->last_eat > tph->tdata->ttd) //+ ((100 * (tph->p_ID - 1) / 1000))
		{
			pthread_mutex_lock(&tph->tdata->msg);
			printf("|%ld philo = %d|\n", get_time() - tph->last_eat, tph->p_ID);
			fflush(stdout);
			print_msg("died", tph, 0);
			tph->tdata->die++;
		}
		pthread_mutex_unlock(&tph->race_eat);
		pthread_mutex_unlock(&tph->tdata->race_die);
		usleep(1);
	}
	return (NULL);
}

void	*death_note(void *death)
{
	t_data *data;

	data = (t_data *)death;
	while (1)
	{
		pthread_mutex_lock(&data->race_die);
		if(data->die)
		{
			return NULL;
		}
		if(data->all_eat >= data->nof)
		{
			pthread_mutex_lock(&data->msg);
			data->die++;
		}
		pthread_mutex_unlock(&data->race_die);
		usleep(1);
	}
	return (NULL);
}

void	*work_p(void *p_tph)
{
	pthread_t die;

	t_ph *tph = (t_ph *)p_tph;
	tph->last_eat = get_time();
	if (pthread_create(&die, NULL, die_conditon, tph))
		return (NULL);
	pthread_detach(die);
	while (1)
	{
		pthread_mutex_lock(&tph->tdata->race_die);
		if(tph->tdata->die)
		{
			pthread_mutex_unlock(&tph->tdata->race_die);
			return (NULL);
		}
		pthread_mutex_unlock(&tph->tdata->race_die);

		rotine(tph);
	}
	return (NULL);
}

int start_thread(t_data *data)
{
	int			i;
	pthread_t	die;

	i = -1;
	data->die = 0;
	data->all_eat = 0;
	if (pthread_create(&die, NULL, death_note, data))
		return (1);
	while (++i < data->nof)
	{
		if (!i)
			data->start = get_time();
		if (pthread_create(&data->tph[i].suqrat, NULL, work_p, &data->tph[i]))
			return (1);
		pthread_detach(data->tph[i].suqrat);
		usleep(55);
	}
	pthread_join(die, NULL);
	return (0);
}
