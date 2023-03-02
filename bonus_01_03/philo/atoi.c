#include "philo.h"

int	my_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (!*str)
		return (-1);
	while ((*str == ' ') || (*str >= 7 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str && (*str >= '0' && *str <= '9'))
	{
		res = (res * 10) + (*str - 48);
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (res * sign);
}
