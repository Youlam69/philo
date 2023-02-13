#include "philo.h"
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

int	forks_init(t_data *data)
{
	int	i;

	i = 0;
	// pthread_mutex_init(&(options->log), NULL);
	pthread_mutex_init(&data->msg, NULL);
	while (i < data->nof)
	{
		printf("problem init fork -l %d\n", i);

		if (pthread_mutex_init(&(data->fork[i]), NULL))
			return (1);
		printf("problem init fork %d\n", i);
		data->tph[i].tdata = data;
		i++;
	}
	return (0);
}

void print_msg(char *tab, int id,pthread_mutex_t print)
{
	printf("print %d\n",id);
	fflush(stdout);
	pthread_mutex_lock(&print);
	printf("ana al faylasof : %d %s\n", id, tab);
	fflush(stdout);
	pthread_mutex_unlock(&print);
}

void	*testr(void *tph)
{
	
	t_ph *p_tph = (t_ph *)tph;
	print_msg("dkhalt", p_tph->p_ID, p_tph->tdata->msg);
	// printf("Ana al faylasof raqem %d dkhalt db nit\n", p_tph->p_ID);
	pthread_mutex_lock(&p_tph->tdata->fork[p_tph->p_ID - 1]);
	print_msg("chdit frchity ana", p_tph->p_ID, p_tph->tdata->msg);
	pthread_mutex_lock(&p_tph->tdata->fork[p_tph->p_ID % p_tph->tdata->nof]);
	print_msg("kan9si", p_tph->p_ID, p_tph->tdata->msg);
	// printf("Ana al faylasof raqem %d dba kan9assi\n", p_tph->p_ID);

	sleep(p_tph->tdata->tte / 1000);
	// 	printf("khrit\n");
	// 	fflush(stdout);
	// 	// write(1,"after eat \n", 11);
	// }
	
	pthread_mutex_unlock(&p_tph->tdata->fork[p_tph->p_ID - 1]);
	pthread_mutex_unlock(&p_tph->tdata->fork[p_tph->p_ID % p_tph->tdata->nof]);
	
	print_msg("sleep", p_tph->p_ID, p_tph->tdata->msg);
	usleep(p_tph->tdata->tts * 1000);
	print_msg("thinking", p_tph->p_ID, p_tph->tdata->msg);


	return(NULL);
}

int c_suqrats(t_data *p)
{
	int i;
	i = 0;

	p->tabphilo = malloc(sizeof(pthread_t) * p->nof);
	p->fork = malloc(sizeof(pthread_mutex_t) * p->nof);
	p->tph = malloc(sizeof(t_ph) * p->nof);
	if (forks_init(p))
	{
		printf("problem init fork 2\n");
		return (1);
	}
	while (i < p->nof)
	{
		// if (i % 2 == 0) {
		// 	printf("here zawji\n");
			p->tph[i].p_ID = i + 1;
			p->tph[i].t_e = 0;
			p->tabphilo[i] = p->tph[i].suqrat;
			if (pthread_create(&p->tabphilo[i], NULL, testr, &p->tph[i]))
				return 1;
			// usleep(200);
		// }
			i++;
	}
	// i = 0;
	// while (i < p->nof)
	// {
	// 	if (i % 2 != 0) {
	// 		printf("here ghayr zawji\n");
	// 		p->tph[i].p_ID = i + 1;
	// 		p->tph[i].t_e = 0;
	// 		p->tabphilo[i] = p->tph[i].suqrat;
	// 		if (pthread_create(&p->tabphilo[i], NULL, testr, &p->tph[i]))
	// 			return 1;
	// 		// usleep(200);
	// 	}
	// 		i++;
	// }

	return 0;
}


int main(int ac, char **av)
{
	// int i;
	t_data p;
	// t_ph  *philo;
	parsing(ac, av, &p);
	if (c_suqrats(&p))
		return 1;
		
}

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