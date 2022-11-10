/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:29 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/27 14:51:38 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	disp_death_mess(t_philo *phil, char *doing, uint64_t time)
{
	int		i;
	char	*str;

	pthread_mutex_lock(&phil->var->mess_m);
	if (deth_prep(phil))
		return (1);
	buff_update(phil->var, &str);
	phil->var->death_flag = 1;
	str = phil->var->str;
	phil->var->buff_count--;
	phil->var->gate_num++;
	i = 12 + num_len((unsigned long long)phil->num + 1) + num_len(time);
	phil->var->str += i;
	phil->var->len[phil->var->to_write] += i;
	pthread_mutex_unlock(&phil->var->mess_m);
	ft_putnbr_str(time, &str);
	str_str(&str, " ms ");
	ft_putnbr_str(phil->num + 1, &str);
	str_str(&str, doing);
	*str = '\0';
	pthread_mutex_unlock(&phil->var->forks[phil->l_fork]);
	pthread_mutex_unlock(&phil->var->forks[phil->r_fork]);
	return (0);
}

static int	deth(t_variables *var, int i)
{
	uint64_t	now_time;

	now_time = get_time();
	if ((unsigned long long)now_time > (unsigned long long)var->philos[i].lim)
	{
		pthread_mutex_lock(&var->rasporyadok);
		if (disp_death_mess(&var->philos[i], \
		" is die\n\0", now_time - var->start))
		{
			pthread_mutex_unlock(&var->heart_attack);
			return (1);
		}
		gate_unlock(var);
		pthread_mutex_unlock(&var->eat_mutex[i]);
		pthread_mutex_unlock(&var->heart_attack);
		return (1);
	}
	return (0);
}

void	*check_thr(void *vari)
{
	t_variables	*var;
	int			i;

	var = vari;
	i = 0;
	while (1)
	{
		custom_sleep(1, var->amount * 2);
		while (i < var->amount)
		{
			pthread_mutex_lock(&var->eat_mutex[i]);
			if (deth(var, i))
				return ((void *)0);
			pthread_mutex_unlock(&var->eat_mutex[i++]);
		}
		i = 0;
	}
}
