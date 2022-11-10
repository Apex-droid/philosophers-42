/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disp_thr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:15 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/27 12:21:15 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	disp_prep(t_variables *var)
{
	int	i;

	i = 0;
	var->len[0] = 0;
	var->len[1] = 0;
	var->gate_num = -1;
	var->buff_count = var->buff_size;
	var->buff[0][0] = '\0';
	var->buff[1][0] = '\0';
	while (i < var->buff_size)
	{
		pthread_mutex_init(&var->writex[0][i], NULL);
		pthread_mutex_init(&var->writex[1][i], NULL);
		pthread_mutex_lock(&var->writex[0][i]);
		pthread_mutex_lock(&var->writex[1][i]);
		i++;
	}
	var->to_print = 1;
	var->to_write = 0;
	var->str = var->buff[var->to_write];
	pthread_mutex_unlock(&var->mu);
}

void	*disp(void *vari)
{
	t_variables	*var;
	int			i;
	int			j;

	var = vari;
	i = 0;
	j = 0;
	disp_prep(var);
	while (i < var->buff_size)
		pthread_mutex_lock(&var->writex[j][i++]);
	while (var->disp_flag)
	{
		pthread_mutex_lock(&var->write_m);
		write(1, var->buff[j], var->len[j]);
		pthread_mutex_unlock(&var->write_m);
		pthread_mutex_unlock(&var->print_m[j]);
		var->len[j] = 0;
		i = 0;
		j = ~j & 1;
		while (i < var->buff_size)
			pthread_mutex_lock(&var->writex[j][i++]);
	}
	return ((void *)0);
}
