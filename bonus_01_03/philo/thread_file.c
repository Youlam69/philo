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

void	anex_die(t_data *data)
{
	if (get_time() - data->last_eat > data->ttd)
	{
		sem_wait(data->msg);
		print_msg("died", data, 0);
		data->die++;
		// sem_post(data->race_die);
		// exit(0);
	}
}

void	*die_conditon(void *death)
{
	t_data	*data;

	data = (t_data *)death;
	while (1)
	{
			// printf("lol");

		sem_wait(data->race_die);
		if (!data->die)
			anex_die(data);
		else
		{
			data->die++;
			sem_post(data->race_die);
			sem_post( data->hold);
			return (NULL);
		}
		sem_post(data->race_die);

		// pthread_mutex_unlock(&data->race_die);
		usleep(2);
	}
	return (NULL);
}

void	death_note(t_data *data)
{
	int	i;
	int	n;

	n = 0;
	i = -1;

	while (++i < data->nof)
	{
		waitpid(data->socrates[i], &n, WNOHANG); 
	}

	sem_post(data->hold);
}

// 	while (1)
// 	{
// 		pthread_mutex_lock(&data->race_die);
// 		if (!data->die)
// 		{
// 			pthread_mutex_lock(&data->race_all_e);//
// 			if (data->all_eat >= data->nof)
// 			{
// 				pthread_mutex_lock(&data->msg);
// 				data->die++;
// 				/////////
// 			}
// 			pthread_mutex_unlock(&data->race_all_e);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&data->race_die);
// 			return (NULL);
// 		}
// 		pthread_mutex_unlock(&data->race_die);
// 		usleep(1);
// 	}

// 	sem_post(data->dial prnt);
// 	exit(1)
// 	return (NULL);
// }

int	work_p(t_data *data)
{
	pthread_t	die;

	data->last_eat = get_time();
	if (pthread_create(&die, NULL, die_conditon, data))
		return (1);
	while (!rotine(data))
	{
		sem_wait(data->race_die);
		if (data->die)
		{
	// printf("process ____________________________________________________________%d %d\n", 888, 555);

			sem_post(data->race_die);
	// 		// return (0);
			sem_post(data->hold);
			break;
		}
		sem_post(data->race_die);
			usleep(1);
	}
	sem_wait(data->race_die);
	data->die++;
	sem_post(data->race_die);

	sem_wait(data->msg);
	sem_post(data->hold);
	pthread_detach(die);
	// exit(0);
	return (0);
}

int foo(int i) {
	printf("yes created: it's me %d with pid = %d\n", i, getpid());
	return 0;
}

int	start_thread(t_data *data)
{
	int	i;
	i = -1;
	data->die = 0;
	pid_t pid;
	sem_wait(data->hold);
	while (++i < data->nof)
	{
		if (!i)
			data->start = get_time();
		data->p_id = i + 1;
		pid = fork();
		if (!pid)
			work_p(data);	
		else if (pid == -1)
			return(1);
		else
		{
			data->socrates[i] = pid;
			usleep(1);
		}
	}
	sem_wait(data->hold);
	printf("process ____________________________________________________________%d %d\n", i, 555);
	if(data->nofe != -1)
		death_note(data);
	while (--i >= 0)
	{
		// sleep(1);
		kill(data->socrates[i], 9);
	}
	
	return (0);
}
