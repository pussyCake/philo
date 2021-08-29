/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantigon <pantigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 20:38:05 by pantigon          #+#    #+#             */
/*   Updated: 2021/07/24 05:09:03 by pantigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_ph
{
	int					i;
	int					count_eat;
	long long			meal;
	struct s_arg		*arg;
	pthread_t			tid;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
}	t_ph;

typedef struct s_arg
{
	int					num;
	int					stop;
	int					stop_eat;
	int					total_eat;
	long				t_die;
	long				t_eat;
	long				t_sleep;
	unsigned long		time_strt;
	t_ph				*phils;
	pthread_mutex_t		main;
	pthread_mutex_t		print;
	pthread_mutex_t		*fork;
}	t_arg;

//init.c
int				init(int ac, char **av, t_arg *arg);

//	live.c
int				start_live(t_arg *arg);
void			*ft_live_phil(void *data);

//utils_phil.c
unsigned long	get_time(void);
void			ft_msleep(unsigned long msec);
void			get_up_from_table(t_arg *arg);
void			ft_put_msq(char *msg, t_ph *phil);
void			ft_put_msq_no_lock(char *msg, t_ph *phil);

// utils_lib.c 
int				ft_atoi(const char *str);
void			ft_putnbr_fd(unsigned long n, int fd);
void			ft_putstr_fd(char *s, int fd);

//error.c
int				error_msq(char *msg);
size_t			ft_strlen(const char *str);

#endif