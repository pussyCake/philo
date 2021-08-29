/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantigon <pantigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/24 03:39:11 by pantigon          #+#    #+#             */
/*   Updated: 2021/07/24 05:13:31 by pantigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_fork(t_arg *arg, t_ph *phil)
{
	if (phil->i == arg->num)
	{
		phil->left = &arg->fork[phil->i - 1];
		phil->right = &arg->fork[0];
	}
	else
	{
		phil->left = &arg->fork[phil->i - 1];
		phil->right = &arg->fork[phil->i];
	}
}

int	create_philo(t_arg *arg)
{
	int		i;

	i = 0;
	arg->time_strt = get_time();
	arg->phils = (t_ph *)malloc(sizeof(t_ph) * arg->num);
	arg->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * arg->num);
	if (!arg->phils || !arg->fork)
		return (error_msq("ERROR: malloc fail\n"));
	memset(arg->phils, 0, sizeof(t_ph) * arg->num);
	memset(arg->fork, 0, sizeof(pthread_mutex_t) * arg->num);
	while (i < arg->num)
	{
		arg->phils[i].i = i + 1;
		if (pthread_mutex_init(&arg->fork[i], NULL))
		{
			free(arg->fork);
			return (error_msq("ERROR: in init mutex\n"));
		}
		get_fork(arg, &arg->phils[i]);
		arg->phils[i].arg = arg;
		i++;
	}
	return (0);
}

void	get_arg(int ac, char **av, t_arg *arg)
{
	arg->stop = 0;
	arg->stop_eat = 0;
	arg->num = ft_atoi(av[1]);
	arg->t_die = ft_atoi(av[2]);
	arg->t_eat = ft_atoi(av[3]);
	arg->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->total_eat = ft_atoi(av[5]);
}

int	check_arg(int ac, t_arg *arg)
{
	if (arg->num <= 0)
		return (error_msq("ERROR: argument incorrect\n"));
	else if (arg->t_die <= 0)
		return (error_msq("ERROR: argument incorrect\n"));
	else if (arg->t_eat <= 0)
		return (error_msq("ERROR: argument incorrect\n"));
	else if (arg->t_sleep <= 0)
		return (error_msq("ERROR: argument incorrect\n"));
	else if (ac == 6 && arg->total_eat <= 0)
		return (error_msq("ERROR: argument incorrect\n"));
	return (0);
}

int	init(int ac, char **av, t_arg *arg)
{
	memset(arg, 0, sizeof(t_arg));
	if (pthread_mutex_init(&arg->main, NULL)
		|| pthread_mutex_init(&arg->print, NULL))
		return (error_msq("ERROR: in init mutex\n"));
	if (ac != 5 && ac != 6)
		return (error_msq("ERROR: argument not 5 or 6\n"));
	get_arg(ac, av, arg);
	if (check_arg(ac, arg))
		return (1);
	if (create_philo(arg))
		return (1);
	pthread_mutex_lock(&arg->main);
	return (0);
}
