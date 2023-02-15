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
	int					all_eat;
	int					die;
	long int			start;
	pthread_mutex_t		msg;
	// pthread_t			*tabphilo
	pthread_mutex_t		*fork;
	struct s_ph			*tph;
}			t_data;

typedef struct	s_ph
{
	int			p_ID;
	int			nt_e;
	long int	last_eat;
	pthread_t	suqrat;
	t_data		*tdata;
}			t_ph;

int			my_atoi(const char *str);
int			parsing(int ac, char **av, t_data *data);
int			start_thread(t_data *data);
long int	get_time(void);
void		*work_p(void *p_tph);
int			rotine(t_ph *tph);
void		print_msg(char *tab, t_ph *tph, int ref);
void		*die_conditon(void *death);
void		*death_note(void *death);
void		dstroy_m(t_data *data);

#endif