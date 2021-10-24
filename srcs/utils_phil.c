
#include "philo.h"

void	get_up_from_table(t_arg *arg)
{
	int		i;

	i = 0;
	free(arg->phils);
	i = 0;
	while (i < arg->num)
		pthread_mutex_destroy(&arg->fork[i++]);
	free(arg->fork);
	pthread_mutex_destroy(&arg->print);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * (unsigned long)1000 + time.tv_usec
		/ (unsigned long)1000);
}

void	ft_msleep(unsigned long msec)
{
	unsigned long	now;
	unsigned long	need;

	now = get_time();
	need = now + msec;
	while (now < need)
	{
		usleep(200);
		now = get_time();
	}
	return ;
}

void	ft_put_msq(char *msg, t_ph *phil)
{
	unsigned long	curr_time;

	pthread_mutex_lock(&phil->arg->print);
	curr_time = get_time();
	ft_putnbr_fd(curr_time - phil->arg->time_strt, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(phil->i, 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
	pthread_mutex_unlock(&phil->arg->print);
}

void	ft_put_msq_no_lock(char *msg, t_ph *phil)
{
	unsigned long	curr_time;

	curr_time = get_time();
	ft_putnbr_fd(curr_time - phil->arg->time_strt, 1);
	ft_putstr_fd("\t", 1);
	ft_putnbr_fd(phil->i, 1);
	ft_putstr_fd(msg, 1);
	ft_putstr_fd("\n", 1);
}
