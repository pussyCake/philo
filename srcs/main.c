/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantigon <pantigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 20:31:55 by pantigon          #+#    #+#             */
/*   Updated: 2021/07/24 05:08:04 by pantigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_arg		arg;

	if (init(ac, av, &arg))
		return (1);
	if (start_live(&arg))
		return (1);
	pthread_mutex_lock(&arg.main);
	pthread_mutex_unlock(&arg.main);
	pthread_mutex_destroy(&arg.main);
	get_up_from_table(&arg);
	return (0);
}
