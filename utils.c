/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 22:52:21 by ylamraou          #+#    #+#             */
/*   Updated: 2023/02/26 22:53:43 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	pthread_mutex_lock(&tph->tdata->race_all_e);
	if (tph->nt_e == tph->tdata->nofe)
		tph->tdata->all_eat++;
	pthread_mutex_unlock(&tph->tdata->race_all_e);
	print_msg("is sleeping", tph, 1);
	usleep(tph->tdata->tts * 1000);
	print_msg("is thinking", tph, 1);
}

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
	long int	time_start;

	time_start = get_time() - tph->tdata->start;
	if (ref)
	{
		pthread_mutex_lock(&tph->tdata->msg);
		if (ref == 2)
		{
			printf("%ld %d %s\n", time_start, tph->p_ID, tab);
			printf("%ld %d %s\n", time_start, tph->p_ID, "is eating");
		}
		else
			printf("%ld %d %s\n", time_start, tph->p_ID, tab);
		pthread_mutex_unlock(&tph->tdata->msg);
	}
	else
		printf("%ld %d %s\n", time_start, tph->p_ID, tab);
}

long int	get_time(void)
{
	struct timeval	t_v;
	long int		t_ms;

	gettimeofday(&t_v, NULL);
	t_ms = ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
	return (t_ms);
}

int	my_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (!*str)
		return (-1);
	while ((*str == ' ') || (*str >= 7 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (res * sign);
}
