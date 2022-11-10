/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:23 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/28 18:17:26 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_dest(t_variables *var)
{
	pthread_mutex_unlock(&var->mess_m);
	pthread_mutex_destroy(&var->mess_m);
	pthread_mutex_unlock(&var->rasporyadok);
	pthread_mutex_destroy(&var->rasporyadok);
	pthread_mutex_unlock(&var->heart_attack);
	pthread_mutex_destroy(&var->heart_attack);
	pthread_mutex_unlock(&var->print_m[0]);
	pthread_mutex_destroy(&var->print_m[0]);
	pthread_mutex_unlock(&var->print_m[1]);
	pthread_mutex_destroy(&var->print_m[1]);
	pthread_mutex_unlock(&var->mu);
	pthread_mutex_destroy(&var->mu);
	pthread_mutex_unlock(&var->write_m);
	pthread_mutex_destroy(&var->write_m);
	pthread_mutex_unlock(&var->check_end);
	pthread_mutex_destroy(&var->check_end);
	pthread_mutex_unlock(&var->stop_end);
	pthread_mutex_destroy(&var->stop_end);
}

static void	clean_mutex(pthread_mutex_t *mutex, int size)
{
	int	i;

	i = 0;
	if (mutex)
	{
		while (i < size)
			pthread_mutex_unlock(&mutex[i++]);
		i = 0;
		while (i < size)
			pthread_mutex_destroy(&mutex[i++]);
	}
	if (mutex)
		free(mutex);
}

int	clean(t_variables *var)
{
	free(var->chairs);
	var->chairs = NULL;
	free(var->philos);
	var->philos = NULL;
	free(var->buff[0]);
	var->buff[0] = NULL;
	free(var->buff[1]);
	var->buff[1] = NULL;
	var->str = NULL;
	unlock_dest(var);
	clean_mutex(var->eat_mutex, var->amount);
	var->eat_mutex = NULL;
	clean_mutex(var->forks, var->amount);
	var->forks = NULL;
	clean_mutex(var->ya_poel, var->amount);
	var->ya_poel = NULL;
	clean_mutex(var->stop, var->amount);
	var->stop = NULL;
	clean_mutex(var->writex[0], var->buff_size);
	var->writex[0] = NULL;
	clean_mutex(var->writex[1], var->buff_size);
	var->writex[1] = NULL;
	return (0);
}
