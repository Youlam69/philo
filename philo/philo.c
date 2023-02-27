/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamraou <ylamraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 23:04:31 by ylamraou          #+#    #+#             */
/*   Updated: 2023/02/26 23:04:43 by ylamraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	get_time(void)
{
	struct timeval	t_v;
	long int		t_ms;

	gettimeofday(&t_v, NULL);
	t_ms = ((t_v.tv_sec * 1000) + (t_v.tv_usec / 1000));
	return (t_ms);
}

int	forks_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->msg, NULL))
		return (1);
	if (pthread_mutex_init(&data->race_all_e, NULL))
		return (1);
	if (pthread_mutex_init(&data->race_die, NULL))
		return (1);
	while (++i < data->nof)
	{
		data->tph[i].p_ID = i + 1;
		data->tph[i].nt_e = 0;
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (1);
		if (pthread_mutex_init(&(data->tph[i].race_eat), NULL))
			return (1);
		data->tph[i].tdata = data;
	}
	return (0);
}

int	c_suqrats(t_data *data)
{
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nof);
	data->tph = malloc(sizeof(t_ph) * data->nof);
	if (forks_init(data))
		return (1);
	if (start_thread(data))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av, &data))
		return (1);
	if (c_suqrats(&data))
		return (1);
	dstroy_m(&data);
	return (0);
}
