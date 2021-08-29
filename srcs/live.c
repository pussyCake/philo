/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantigon <pantigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 20:39:07 by pantigon          #+#    #+#             */
/*   Updated: 2021/07/24 05:28:15 by pantigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_death(void *data)
{
	t_arg	*arg;
	int		i;
	long	curr;

	arg = (t_arg *)data;
	while (arg->stop == 0)
	{
		i = 0;
		while (i < arg->num)
		{
			curr = get_time();
			if ((curr - arg->phils[i].meal) > arg->t_die)
			{
				pthread_mutex_lock(&arg->print);
				ft_put_msq_no_lock("\033[31m		died\033[0m", &arg->phils[i]);
				arg->stop = 1;
				pthread_mutex_unlock(&arg->main);
				return (0);
			}
			usleep(100);
			i++;
		}
	}
	return (0);
}

void	*check_num_meal(void *data)
{
	t_arg	*arg;

	arg = (t_arg *)data;
	while (arg->stop == 0)
	{
		if (arg->stop_eat == arg->num && arg->stop == 0)
		{
			arg->stop = 1;
			pthread_mutex_lock(&arg->print);
			pthread_mutex_unlock(&arg->main);
		}
	}
	return (0);
}

void	*phil_eat(t_ph *phil)
{
	pthread_mutex_lock(phil->left);
	ft_put_msq("		has taken a fork", phil);
	pthread_mutex_lock(phil->right);
	ft_put_msq("		has taken a fork", phil);
	ft_put_msq("\033[32m		is eating\033[0m", phil);
	phil->meal = get_time();
	ft_msleep(phil->arg->t_eat);
	phil->count_eat += 1;
	if (phil->count_eat == phil->arg->total_eat)
		phil->arg->stop_eat += 1;
	pthread_mutex_unlock(phil->left);
	pthread_mutex_unlock(phil->right);
	return (0);
}

void	*ft_live_phil(void *data)
{
	t_ph	*phil;

	phil = (t_ph *)data;
	phil->meal = get_time();
	if (phil->i % 2 == 0)
		ft_msleep(phil->arg->t_eat);
	while (1)
	{
		phil_eat(phil);
		ft_put_msq("\033[36m		is sleeping\033[0m", phil);
		ft_msleep(phil->arg->t_sleep);
		ft_put_msq("\033[33m		is thinking\033[0m", phil);
	}
	return (0);
}

int	start_live(t_arg *arg)
{
	int			i;
	pthread_t	tid;

	i = 0;
	if (arg->total_eat)
	{
		if (pthread_create(&tid, NULL, check_num_meal, arg))
			return (error_msq("ERROR: in thread create (monitore eat)"));
	}
	while (i < arg->num)
	{
		if (pthread_create(&arg->phils[i].tid, NULL, ft_live_phil,
				&arg->phils[i]))
			return (error_msq("ERROR: in thread philo create"));
		pthread_detach(arg->phils[i].tid);
		i++;
	}
	if (pthread_create(&tid, NULL, check_death, arg))
		return (error_msq("ERROR: in thread create (monitore death)"));
	pthread_detach(tid);
	return (0);
}
