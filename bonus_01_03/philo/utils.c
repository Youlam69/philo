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

int	rotine(t_data *data)
{
	if(!data->nofe)
		return (1);

	sem_wait(data->fork );
	print_msg("has taken a fork", data, 1);
	sem_wait(data->fork);
	print_msg("has taken a fork", data, 2);
	
	sem_wait(data->race_die);
	data->last_eat = get_time();
	sem_post(data->race_die);

	usleep(data->tte * 1000);

	sem_post(data->fork);
	sem_post(data->fork);

	data->nofe--;
	// sem_wait(&data->race_all_e);
	// if (tph->nt_e == data->nofe)
	// 	data->all_eat++;
	// sem_post(&data->race_all_e);
	print_msg("is sleeping", data, 1);
	usleep(data->tts * 1000);
	print_msg("is thinking",data, 1);
	return (0);
}
	
// void	wait_destroy(t_data *data)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->race_die);
// 		if (data->die >= data->nof)
// 		{
// 			pthread_mutex_unlock(&data->race_die);
// 			return ;
// 		}
// 		pthread_mutex_unlock(&data->race_die);
// 		usleep(1);
// 	}
// }

// void	dstroy_m(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	wait_destroy(data);
// 	free(data->tph);
// 	data->tph = NULL;
// 	pthread_mutex_destroy(&(data->msg));
// 	while (++i < data->nof)
// 		pthread_mutex_destroy(&data->fork[i]);
// 	free(data->fork);
// }

void	print_msg(char *tab, t_data *data, int ref)
{
	long int	time_start;

	time_start = get_time() - data->start;
	if (ref)
	{
		sem_wait(data->msg);
		if (ref == 2)
		{
			printf("%ld %d %s\n", time_start, data->p_id, tab);
			printf("%ld %d %s\n", time_start, data->p_id, "is eating");
		}
		else
			printf("%ld %d %s\n", time_start, data->p_id, tab);
		sem_post(data->msg);
	}
	else
		printf("%ld %d %s\n", time_start, data->p_id, tab);
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
