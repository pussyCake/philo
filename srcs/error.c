
#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (0);
	while (str[count] != '\0')
		count++;
	return (count);
}

int	error_msq(char *msg)
{
	write(2, msg, ft_strlen(msg));
	return (1);
}
