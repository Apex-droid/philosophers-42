/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:57 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 19:51:49 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*check_eat(void *vars)
{
	int			i;
	t_variables	*var;

	var = vars;
	sem_wait(var->check_end);
	while (var->must_eat_count && var->death_flag)
	{
		sem_post(var->check_end);
		while (i < var->amount)
		{
			sem_wait(var->philos[i].ya_poel);
			i++;
		}
		i = 0;
		var->must_eat_count--;
		sem_wait(var->check_end);
	}
	var->steward_d = 0;
	sem_post(var->check_end);
	sem_post(var->heart_attack);
	return ((void *)1);
}
