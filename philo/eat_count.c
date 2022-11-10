/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:57 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/27 12:20:57 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	disp_end(t_variables *var)
{
	int		j;
	char	*str;

	pthread_mutex_lock(&var->mess_m);
	if (var->death_flag)
	{
		pthread_mutex_unlock(&var->stop_end);
		pthread_mutex_unlock(&var->mess_m);
		return (1);
	}
	buff_update(var, &str);
	var->death_flag = 1;
	str = var->str;
	var->buff_count--;
	var->gate_num++;
	var->str++;
	pthread_mutex_unlock(&var->mess_m);
	j = var->gate_num;
	*str = '\0';
	return (0);
}

void	*check_eat(void *vars)
{
	int			i;
	t_variables	*var;

	var = vars;
	var->steward_d = 1;
	while (var->must_eat_count)
	{
		while (i < var->amount)
		{
			pthread_mutex_lock(&var->ya_poel[i]);
			i++;
		}
		i = 0;
		var->must_eat_count--;
	}
	pthread_mutex_lock(&var->check_end);
	var->steward_d = 0;
	pthread_mutex_unlock(&var->check_end);
	pthread_mutex_lock(&var->rasporyadok);
	disp_end(var);
	gate_unlock(var);
	pthread_mutex_unlock(&var->stop_end);
	pthread_mutex_unlock(&var->heart_attack);
	return ((void *)1);
}
