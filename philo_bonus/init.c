/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:45 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 19:50:37 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sem_long(t_variables *var, int size)
{
	int		i;
	char	*str;

	i = 0;
	while (i < size)
	{
		str = ft_itoa(i);
		sem_unlink(str);
		var->philos[i].eat_mutex \
		= sem_open((const char *)str, O_CREAT, O_EXCL, 1);
		free(str);
		str = NULL;
		i++;
	}
}

static void	sem_long1(t_variables *var, int size)
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
		sem_unlink(str1);
		var->philos[i].ya_poel = \
		sem_open((const char *)str1, O_CREAT, O_EXCL, 0);
		free(num);
		num = NULL;
		free(str1);
		str1 = NULL;
		i++;
	}
}

static void	philo_init(t_variables *var)
{
	int	i;

	i = 0;
	while (i < var->amount)
	{
		var->philos[i].num = i;
		var->philos[i].r_fork = (i + 1) % var->amount;
		var->philos[i].var = var;
		var->philos[i].is_eating = 0;
		i++;
	}
}

static void	alone_sem(t_variables *var)
{
	sem_unlink("f");
	var->forks = sem_open("f", O_CREAT, 0777, var->amount);
	sem_unlink("a");
	var->heart_attack = sem_open("a", O_CREAT, 0777, 0);
	sem_unlink("p1");
	var->print_m[0] = sem_open("p1", O_CREAT, 0777, 1);
	sem_unlink("p2");
	var->print_m[1] = sem_open("p2", O_CREAT, 0777, 1);
	sem_unlink("r");
	var->rasporyadok = sem_open("r", O_CREAT, 0777, 1);
	sem_unlink("mm");
	var->mess_m = sem_open("mm", O_CREAT, 0777, 1);
	sem_unlink("ch");
	var->check_end = sem_open("ch", O_CREAT, 0777, 1);
	sem_unlink("s");
	var->stop_end = sem_open("s", O_CREAT, 0777, 0);
	sem_unlink("mu");
	var->mu = sem_open("mu", O_CREAT, 0777, 0);
	sem_unlink("wm");
	var->write_m = sem_open("wm", O_CREAT, 0777, 1);
	sem_unlink("yap");
}

int	var_init(t_variables *var)
{
	alone_sem(var);
	var->death_flag = 1;
	var->steward_d = 1;
	if (var->time_to_eat < 100)
		var->buff_size = var->amount * 8;
	else if (var->time_to_eat < 500)
		var->buff_size = var->amount * 4;
	else if (var->time_to_eat < 1000)
		var->buff_size = var->amount * 2;
	else
		var->buff_size = var->amount;
	if (kucha_mala(var))
		return (1);
	philo_init(var);
	sem_long(var, var->amount);
	sem_long1(var, var->amount);
	return (0);
}
