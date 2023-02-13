#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>


typedef struct s_data
{
	int					ttd;
	int					tte;
	int					tts;
	int					nof;
	int					nofe;
	int					death;
	pthread_mutex_t		msg;
	pthread_t			*tabphilo;
	pthread_mutex_t		*fork;
	struct s_ph			*tph;

}			t_data;


typedef struct	s_ph
{
	int			p_ID;
	int			t_e;
	pthread_t	suqrat;
	t_data		*tdata;
}			t_ph;


int	my_atoi(const char *str);
int parsing(int ac, char **av, t_data *p);


#endif