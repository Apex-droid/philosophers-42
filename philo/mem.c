/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:33 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/28 23:03:47 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	free_some(void *some)
{
	if (some)
		free(some);
	some = NULL;
}

static void	urgently_free(t_variables *var)
{
	free_some((void *)var->chairs);
	free_some((void *)var->philos);
	free_some((void *)var->buff[1]);
	free_some((void *)var->buff[0]);
	free_some((void *)var->stop);
	free_some((void *)var->ya_poel);
	free_some((void *)var->eat_mutex);
	free_some((void *)var->writex[0]);
	free_some((void *)var->writex[1]);
	free_some((void *)var->forks);
	free_some((void *)var->mojna_jrat);
}

static void	nulson(t_variables *var)
{
	var->chairs = NULL ;
	var->philos = NULL;
	var->buff[1] = NULL;
	var->buff[0] = NULL;
	var->stop = NULL;
	var->ya_poel = NULL;
	var->eat_mutex = NULL;
	var->writex[0] = NULL;
	var->writex[1] = NULL;
	var->forks = NULL;
}

static void	kucha_sovsem_mala(t_variables *var)
{
	var->mojna_jrat = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->amount);
	var->chairs = (pthread_t *)malloc(sizeof(pthread_t) * var->amount);
	var->philos = (t_philo *)malloc(sizeof(t_philo) * var->amount);
	var->buff[1] = (char *)malloc(var->buff_size * sizeof(char) * 65);
	var->buff[0] = (char *)malloc(var->buff_size * sizeof(char) * 65);
	var->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->amount);
}

int	kucha_mala(t_variables *var)
{
	nulson(var);
	kucha_sovsem_mala(var);
	var->stop = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->amount);
	var->ya_poel = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->amount);
	var->eat_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->amount);
	var->writex[0] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->buff_size);
	var->writex[1] = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) \
	* var->buff_size);
	if (!(var->chairs && var->philos && var->buff[1] && var->buff[0] \
	&& var->forks && var->stop && var->ya_poel && var->eat_mutex && \
	var->writex[0] && var->writex[1]) && var->mojna_jrat)
	{
		urgently_free(var);
		return (1);
	}
	return (0);
}
