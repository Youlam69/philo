#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <semaphore.h>

// # include <string.h>


typedef struct s_data
{
	int					ttd;
	int					tte;
	int					tts;
	int					nof;
	int					nofe;
	// int					all_eat;
	int					die;
	// int					nt_e;
	pid_t				*socrates;
	int					p_id;
	long int			start;
	long int			last_eat;
	sem_t				*msg;
	sem_t				*hold;
	sem_t				*race_die;
	// sem_t				*race_all_e;
	// sem_t				*race_eat;
	sem_t				*fork;
	struct s_ph			*tph;
}			t_data;

// typedef struct s_data
// {
// 	int					ttd;
// 	int					tte;
// 	int					tts;
// 	int					nof;
// 	int					nofe;
// 	int					all_eat;
// 	int					die;
// 	long int			start;
// 	pthread_mutex_t		msg;
// 	pthread_mutex_t		race_die;
// 	pthread_mutex_t		race_all_e;
// 	pthread_mutex_t		*fork;
// 	struct s_ph			*tph;
// }			t_data;

// typedef struct	s_ph
// {
// 	int					p_ID;
// 	int					nt_e;
// 	long int			last_eat;
// 	pthread_t			suqrat;
// 	pthread_mutex_t		race_eat;
// 	t_data				*tdata;
// }			t_ph;

int			my_atoi(const char *str);
int			parsing(int ac, char **av, t_data *data);
int			start_thread(t_data *data);
long int	get_time(void);
int			work_p(t_data *data);
int			rotine(t_data *data);
void		print_msg(char *tab, t_data *data, int ref);
void		*die_conditon(void *death);
void		death_note(t_data *data);
void		dstroy_m(t_data *data);

#endif
