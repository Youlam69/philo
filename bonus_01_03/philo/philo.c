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
	sem_unlink("forks");
	sem_unlink("msg");
	sem_unlink("die");
	sem_unlink("hold");
	data->fork = sem_open("forks", O_CREAT, 666, data->nof);
	data->msg = sem_open("msg", O_CREAT, 666, 1);
	data->hold = sem_open("hold", O_CREAT, 666, 1);
	data->race_die = sem_open("die", O_CREAT, 666, 1);
	return (0);
}

int	c_suqrats(t_data *data)
{
	// int i = 0;
	data->socrates = malloc(sizeof(pid_t) * data->nof);

	// data->fork = malloc(sizeof(pthread_mutex_t) * data->nof);
	// data->tph = malloc(sizeof(t_ph) * data->nof);
	if (forks_init(data))
		return (1);
	if (start_thread(data))
		return (1);
	if(data->nofe != -1)
		death_note(data);
	
	// sem_wait(data->hold);
	
	// i = 0;
	
	// while (i <= data->nof)
	// {
	// 	sleep(1);
	// 	kill(data->socrates[i], 9);
	// 	// printf("process ____________________________________________________________%d %d\n", i, data->socrates[i]);
	// 	// --i;
	// }
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parsing(ac, av, &data))
		return (1);
	if (c_suqrats(&data))
		return (1);
	
	// dstroy_m(&data);
	return (0);
}
