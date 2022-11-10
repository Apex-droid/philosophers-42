/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:23 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 20:00:46 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	unlock_dest(t_variables *var)
{
	sem_close(var->mess_m);
	sem_unlink("mm");
	sem_close(var->rasporyadok);
	sem_unlink("r");
	sem_close(var->heart_attack);
	sem_unlink("a");
	sem_close(var->print_m[0]);
	sem_unlink("p1");
	sem_close(var->print_m[1]);
	sem_unlink("p2");
	sem_close(var->mu);
	sem_unlink("mu");
	sem_close(var->write_m);
	sem_unlink("wm");
	sem_close(var->check_end);
	sem_unlink("ch");
	sem_close(var->stop_end);
	sem_unlink("s");
	sem_close(var->forks);
	sem_unlink("f");
}

static void	clean_sem(t_variables *var, int size)
{
	int		i;
	char	*str;

	i = 0;
	while (i < size)
	{
		str = ft_itoa(i);
		sem_close(var->philos[i].eat_mutex);
		sem_unlink((const char *)str);
		free(str);
		str = NULL;
		var->philos[i].eat_mutex = NULL;
		i++;
	}
}

static void	clean_sem1(t_variables *var, int size)
{
	int		i;
	char	*num;
	char	*str1;
	char	str[2];

	str[0] = 'e';
	str[1] = '\0';
	i = 0;
	while (i < size)
	{
		num = ft_itoa(i);
		str1 = ft_strjoin(num, str);
		sem_close(var->philos[i].ya_poel);
		sem_unlink((const char *)str1);
		free(num);
		num = NULL;
		free(str1);
		str1 = NULL;
		var->philos[i].ya_poel = NULL;
		i++;
	}
}

int	clean(t_variables *var)
{
	free(var->buff[0]);
	var->buff[0] = NULL;
	free(var->buff[1]);
	var->buff[1] = NULL;
	var->str = NULL;
	unlock_dest(var);
	sem_close(var->writex[0]);
	sem_unlink("wx1");
	sem_close(var->writex[1]);
	sem_unlink("wx2");
	clean_sem(var, var->amount);
	clean_sem1(var, var->amount);
	free(var->philos);
	var->philos = NULL;
	return (0);
}
