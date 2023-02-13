#include "philo.h"
static void	init_prm(t_data *p)
{
	p->nof  = -1;
	p->ttd  = -1;
	p->tte = -1;
	p->tts = -1;
	p->nofe = -1;
}

int data(t_data *p, int ac, char **av)
{
	init_prm(p);
	p->nof = my_atoi(av[1]);
	p->ttd = my_atoi(av[2]);
	p->tte = my_atoi(av[3]);
	p->tts = my_atoi(av[4]);
	if (p->nof < 0 || p->ttd < 0 || p->tte < 0 || p->tts < 0)
		return (-1);
	if (ac == 6)
	{
		p->nofe = my_atoi(av[5]);
		if(p->nofe <= 0)
			return (-1);
	}
	return (0);

}

int parsing(int ac, char **av, t_data *p)
{
	if (ac <= 4 || ac >= 7)
	{
		printf("error nbr prams\n");
		exit(1);
	}
	if (data(p, ac, av) < 0)
	{
		printf("error :> not invalid arguments\n");
		exit(1);
	}
	return 0;
}
