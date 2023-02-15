#include "philo.h"


// int	rotine(t_ph *tph)
// {
// 	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID - 1]);
// 	print_msg("take a fork", tph, 1);
// 	pthread_mutex_lock(&tph->tdata->fork[tph->p_ID % tph->tdata->nof]);
// 	print_msg("take a fork", tph, 2);
// 	usleep(tph->tdata->tte * 1000);
// 	tph->last_eat = get_time();
// 	pthread_mutex_unlock(&tph->tdata->fork[tph->p_ID - 1]);
// 	pthread_mutex_unlock(&tph->tdata->fork[tph->p_ID % tph->tdata->nof]);
// 	tph->nt_e++;
// 	if (tph->nt_e == tph->tdata->nofe)
// 		tph->tdata->all_eat++;
// 	print_msg("sleep", tph, 1);
// 	usleep(tph->tdata->tts * 1000);
// 	print_msg("thinking", tph, 1);
// 	return(0);
// }

// void	*die_conditon(void *death)
// {
// 	t_ph *tph;

// 	tph = (t_ph *)death;
// 	while(!tph->tdata->die)
// 	{
// 		if (get_time() - tph->last_eat >= tph->tdata->ttd)
// 		{
// 			pthread_mutex_lock(&tph->tdata->msg);
// 			tph->tdata->die++;
// 			print_msg("die", tph, 0);
// 		}
// 	}
// 	return (NULL);
// }

// void	*work_p(void *p_tph)
// {
// 	pthread_t die;

// 	t_ph *tph = (t_ph *)p_tph;
// 	if (pthread_create(&die, NULL, die_conditon, tph))
// 		return (NULL);
// 	while (!tph->tdata->die)
// 		rotine(tph);
// 	pthread_detach(die);
// 	return (NULL);
// }

// void	*death_note(void *death)
// {
// 	t_data *data;

// 	data = (t_data *)death;
// 	while(!data->die)
// 	{
// 		if((data->all_eat >= data->nof))
// 		{
// 			pthread_mutex_lock(&data->msg);
// 			data->die++;
// 		}
// 	}
// 	return (NULL);
// }

// int start_thread(t_data *data)
// {
// 	int			i;
// 	pthread_t	die;

// 	if (pthread_create(&die, NULL, death_note, data))
// 		return (1);
// 	i = -1;
// 	data->die = 0;
// 	data->all_eat = 0;
// 	while (++i < data->nof)
// 	{
// 		data->tph[i].p_ID = i + 1;
// 		data->tph[i].nt_e = 0;
// 		if (!i)
// 			data->start = get_time();
// 		data->tph[i].last_eat = data->start;
// 		if (pthread_create(&data->tph[i].suqrat, NULL, work_p, &data->tph[i]))
// 			return (1);
// 		pthread_detach(data->tph[i].suqrat);
// 		usleep(69);
// 	}
// 	pthread_join(die, NULL);
// 	return (0);
// }

int	forks_init(t_data *data)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&data->msg, NULL))
		return(1);
	while (++i < data->nof)
	{
		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (1);
		data->tph[i].tdata = data;
	}
	return (0);
}

int c_suqrats(t_data *data)
{
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nof);
	data->tph = malloc(sizeof(t_ph) * data->nof);
	if (forks_init(data))
		return (1);
	if(start_thread(data))
		return (1);
	return 0;
}

int main(int ac, char **av)
{
	t_data data;

	if (parsing(ac, av, &data))
		return (1);
	if (c_suqrats(&data))
		return (1);
	dstroy_m(&data);
}

// static void	init_prm(t_philo *p)
// {
// 	p->nof  = -1;
// 	p->ttd  = -1;
// 	p->tte = -1;
// 	p->tts = -1;
// 	p->nofe = -1;
// 	// arguments->death = 0;
// 	// arguments->zero_time = 0;
// 	// arguments->everyone_ate = 0;
// }
// int data(t_philo *p, int ac, char **av)
// {
// 	init_prm(p);
// 	p->nof = my_atoi(av[1]);
// 	p->ttd = my_atoi(av[2]);
// 	p->tte = my_atoi(av[3]);
// 	p->tts = my_atoi(av[4]);
// 	if (p->nof < 0 || p->ttd < 0 || p->tte < 0 || p->tts < 0)
// 		return (-1);
// 	if (ac == 6)
// 	{
// 		p->nofe = my_atoi(av[5]);
// 		if(p->nofe <= 0)
// 			return (-1);
// 	}
// 	return (0);

// }
// int parssing(int ac, char **av, t_philo *p)
// {
// 	if (ac <= 4 || ac >= 7)
// 	{
// 		printf("error nbr prams\n");
// 		exit(1);
// 	}
// 	if (data(p, ac, av) < 0)
// 	{
// 		printf("error :> not invalid arguments\n");
// 		exit(1);
// 	}
// }

	// if (ac <= 4 || ac >= 7)
	// {
	// 	printf("error nbr pram\n");
	// 	return (1);
	// }
	// if (data(&p, ac, av) < 0)
	// {
	// 	printf("error :> not invalid arguments\n");
	// 	return (1);
	// }
	// p = (t_philo *)malloc(sizeof(t_philo));
// }

	// printf("p.nof : %d\n", p.nof);    //
	// printf("p.tte : %d\n", p.tte);   // 
	// printf("p.ttd : %d\n", p.ttd);  //
	// printf("p.tts : %d\n", p.tts); //   
	// if (ac == 6)
	// {

	// 	printf("p.nofe  %d\n",p.nofe);    
	// }
	// if (p.nof <= 0 || p.ttd <= 0 || p.tte <= 0 || p.tts  <= 0 || p.nof  <= 0)
	// {
	// 	printf("error nbr pram\n");
	// 	return (-1);
	// }
	// philo = (t_ph *)malloc(sizeof(t_ph) * p.nof);
	// int hi;
	// while (i < p.nof)
	// {
	// 	philo[i].p_ID = i + 1;
	// 	philo[i].n_e = 0;
	// 	hi = pthread_create(philo[i].suqrat NULL, &test,     )

	// }

// }



/****************************************************************/
// #include "philo.h"

// void *philosopher_thread(void *arg)
// {
//     t_ph *philosopher = (t_ph*)arg;
//     int id = philosopher->p_ID;
//     int eat_time = philosopher->t_e;
//     int left_fork = id;
//     int right_fork = (id + 1) % philosopher->sphilo.nof  ;
//     while (1)
//     {
//         // thinking state
//         printf("%d is thinking\n", id);
//         usleep(philosopher->sphilo.tts * 1000);

//         // try to pick up left fork
//         pthread_mutex_lock(&philosopher->sphilo.fork[left_fork]);
//         printf("%d has taken fork %d\n", id, left_fork);

//         // try to pick up right fork
//         pthread_mutex_lock(&philosopher->sphilo.fork[right_fork]);
//         printf("%d has taken fork %d\n", id, right_fork);

//         // eating state
//         printf("%d is eating\n", id);
//         usleep(eat_time * 1000);

//         // release forks
//         pthread_mutex_unlock(&philosopher->sphilo.fork[left_fork]);
//         pthread_mutex_unlock(&philosopher->sphilo.fork[right_fork]);

//         // sleeping state
//         printf("%d is sleeping\n", id);
//         usleep(philosopher->sphilo.tts * 1000);
//     }
// }

// int main(int ac, char **av)
// {
//     int i;
//     t_philo p;
//     t_ph  *philo;
//     parssing(ac, av, &p);

//     // allocate space for the forks and initialize mutexes
//     p.fork = malloc(sizeof(pthread_mutex_t) * p.nof);
//     for (i = 0; i < p.nof; i++)
//         pthread_mutex_init(&p.fork[i], NULL);

//     // allocate space for the philosopher threads
//     philo = malloc(sizeof(t_ph) * p.nof);
// 	philo->sphilo = p;
//     // create philosopher threads
//     for (i = 0; i < p.nof; i++)
//     {
//         philo[i].p_ID = i;
//         philo[i].t_e = p.tte / p.nof;
//         pthread_create(&philo[i].suqrat, NULL, philosopher_thread, &philo[i]);
//     }

//     // wait for philosopher threads to finish
//     for (i = 0; i < p.nof; i++)
//         pthread_join(philo[i].suqrat, NULL);

//     // clean up
//     for (i = 0; i < p.nof; i++)
//         pthread_mutex_destroy(&p.fork[i]);
//     free(p.fork);
//     free(philo);

//     return 0;
// }
/****************************************************************/