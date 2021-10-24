
#include "philo.h"

int	ft_add_atoi(int check)
{
	if (check > 0)
		return (-1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int				i;
	unsigned int	res;
	unsigned int	rres;
	int				check;

	check = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' && str[i + 1] >= '0' && str[i + 1] <= '9')
		i++;
	else if (str[i] == '-' && str[i + 1] >= '0' && str[i + 1] <= '9')
	{
		i++;
		check = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		rres = res;
		res = (res * 10) + (str[i++] - '0');
		if (rres > res)
			return (ft_add_atoi(check));
	}
	return (res * check);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(unsigned long n, int fd)
{
	if (n < 0)
	{
		n = n * -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10)
	{
		return (ft_putchar_fd(n + '0', fd));
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		return (ft_putchar_fd((n % 10) + '0', fd));
	}
}
