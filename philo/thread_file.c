/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:53:32 by ylamraou          #+#    #+#             */
/*   Updated: 2023/02/26 22:59:07 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	anex_die(t_ph *tph)
{
	pthread_mutex_lock(&tph->race_eat);
	if (get_time() - tph->last_eat > tph->tdata->ttd)
	{
		pthread_mutex_lock(&tph->tdata->msg);
		print_msg("died", tph, 0);
		tph->tdata->die++;
	}
	pthread_mutex_unlock(&tph->race_eat);
}

void	*die_conditon(void *death)
{
	t_ph	*tph;

	tph = (t_ph *)death;
	while (1)
	{
		pthread_mutex_lock(&tph->tdata->race_die);
		if (!tph->tdata->die)
			anex_die(tph);
		else
		{
			tph->tdata->die++;
			pthread_mutex_unlock(&tph->tdata->race_die);
			return (NULL);
		}
		pthread_mutex_unlock(&tph->tdata->race_die);
		usleep(1);
	}
	return (NULL);
}

void	*death_note(void *death)
{
	t_data	*data;

	data = (t_data *)death;
	while (1)
	{
		pthread_mutex_lock(&data->race_die);
		if (!data->die)
		{
			pthread_mutex_lock(&data->race_all_e);
			if (data->all_eat >= data->nof)
			{
				pthread_mutex_lock(&data->msg);
				data->die++;
			}
			pthread_mutex_unlock(&data->race_all_e);
		}
		else
		{
			pthread_mutex_unlock(&data->race_die);
			return (NULL);
		}
		pthread_mutex_unlock(&data->race_die);
		usleep(1);
	}
	return (NULL);
}

void	*work_p(void *p_tph)
{
	pthread_t	die;
	t_ph		*tph;

	tph = (t_ph *)p_tph;
	tph->last_eat = get_time();
	if (pthread_create(&die, NULL, die_conditon, tph))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&tph->tdata->race_die);
		if (tph->tdata->die)
		{
			pthread_mutex_unlock(&tph->tdata->race_die);
			return (NULL);
		}
		pthread_mutex_unlock(&tph->tdata->race_die);
		rotine(tph);
		usleep(1);
	}
	pthread_detach(die);
	return (NULL);
}

int	start_thread(t_data *data)
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
