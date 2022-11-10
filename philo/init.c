/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:45 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 20:19:38 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	mutex_init(t_variables *var, int i)
{
	pthread_mutex_init(&var->forks[i], NULL);
	pthread_mutex_init(&var->stop[i], NULL);
	pthread_mutex_lock(&var->stop[i]);
	pthread_mutex_init(&var->eat_mutex[i], NULL);
	pthread_mutex_init(&var->ya_poel[i], NULL);
	pthread_mutex_lock(&var->ya_poel[i]);
	pthread_mutex_init(&var->mojna_jrat[i], NULL);
	pthread_mutex_lock(&var->mojna_jrat[i]);
}

static void	philo_init(t_variables *var)
{
	int	i;

	i = 0;
	while (i < var->amount)
	{
		var->philos[i].num = i;
		var->philos[i].l_fork = i;
		var->philos[i].r_fork = (i + 1) % var->amount;
		mutex_init(var, i);
		var->philos[i].var = var;
		var->philos[i].is_eating = 0;
		i++;
	}
}

static void	alone_mut(t_variables *var)
{
	pthread_mutex_init(&var->heart_attack, NULL);
	pthread_mutex_init(&var->print_m[0], NULL);
	pthread_mutex_init(&var->print_m[1], NULL);
	pthread_mutex_init(&var->rasporyadok, NULL);
	pthread_mutex_init(&var->mess_m, NULL);
	pthread_mutex_init(&var->check_end, NULL);
	pthread_mutex_init(&var->stop_end, NULL);
	pthread_mutex_lock(&var->stop_end);
	pthread_mutex_lock(&var->heart_attack);
	pthread_mutex_init(&var->mu, NULL);
	pthread_mutex_lock(&var->mu);
}

int	var_init(t_variables *var)
{
	alone_mut(var);
	var->disp_flag = 1;
	var->death_flag = 0;
	if (var->time_to_eat + var->time_to_sl < 200)
		var->buff_size = var->amount * 8;
	else if (var->time_to_eat + var->time_to_sl < 1000)
		var->buff_size = var->amount * 4;
	else if (var->time_to_eat + var->time_to_sl < 2000)
		var->buff_size = var->amount * 2;
	else
		var->buff_size = var->amount;
	if (kucha_mala(var))
		return (1);
	philo_init(var);
	return (0);
}
