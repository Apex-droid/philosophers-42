/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:33 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 09:18:42 by ahelper          ###   ########.fr       */
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
	free_some((void *)var->philos);
	free_some((void *)var->buff[1]);
	free_some((void *)var->buff[0]);
	free_some((void *)var->writex[0]);
	free_some((void *)var->writex[1]);
}

static void	nulson(t_variables *var)
{
	var->philos = NULL;
	var->buff[1] = NULL;
	var->buff[0] = NULL;
	var->writex[0] = NULL;
	var->writex[1] = NULL;
}

int	kucha_mala(t_variables *var)
{
	nulson(var);
	var->philos = (t_philo *)malloc(sizeof(t_philo) * var->amount);
	var->buff[1] = (char *)malloc(var->buff_size * sizeof(char) * 65);
	var->buff[0] = (char *)malloc(var->buff_size * sizeof(char) * 65);
	if (!(var->philos && var->buff[1] && var->buff[0]))
	{
		urgently_free(var);
		return (1);
	}
	return (0);
}
