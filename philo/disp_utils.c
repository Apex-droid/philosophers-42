/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:07 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/29 00:10:54 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	buff_update(t_variables *var, char **str)
{
	if (!var->buff_count)
	{
		pthread_mutex_lock(&var->print_m[var->to_print]);
		var->gate_num = -1;
		var->buff_count = var->buff_size;
		var->to_print = var->to_write;
		var->to_write = ~(var->to_write) & 1;
		var->str = var->buff[var->to_write];
		*str = var->str;
	}
}

void	gate_unlock(t_variables *var)
{
	while (var->gate_num < var->buff_size)
	{
		pthread_mutex_unlock(&var->writex[var->to_write][var->gate_num]);
		var->gate_num++;
	}
}

int	deth_prep(t_philo *phil)
{
	if (phil->var->death_flag)
	{
		pthread_mutex_unlock(&phil->var->write_m);
		pthread_mutex_unlock(&phil->var->forks[phil->l_fork]);
		pthread_mutex_unlock(&phil->var->stop[phil->num]);
		pthread_mutex_unlock(&phil->var->mojna_jrat[phil->num]);
		pthread_mutex_unlock(&phil->var->eat_mutex[phil->num]);
		pthread_mutex_unlock(&phil->var->forks[phil->r_fork]);
		pthread_mutex_unlock(&phil->var->mess_m);
		return (1);
	}
	return (0);
}
