#include <stdio.h>
#include <unistd.h>
#include "philo.h"
#include <pthread.h>

void	*f(void *t)
{
	while(1);
}

int	main()
{
	pthread_t testThread;
	
	pthread_create(&testThread, NULL, f, NULL);
	// pthread_join(testThread,NULL);
	return 0;

}
