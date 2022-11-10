/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:13 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 20:15:26 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	disp_mess(t_philo *phil, char *doing, uint64_t time, int doing_len)
{
	pthread_mutex_t	*mut;
	char			*str;
	int				i;

	pthread_mutex_lock(&phil->var->mess_m);
	if (deth_prep(phil))
		return (1);
	buff_update(phil->var, &str);
	str = phil->var->str;
	i = 4 + doing_len + \
	num_len((unsigned long long)(phil->num + 1)) + num_len(time);
	phil->var->str += i;
	phil->var->len[phil->var->to_write] += i;
	*(phil->var->str) = '\0';
	phil->var->buff_count--;
	phil->var->gate_num++;
	mut = &phil->var->writex[phil->var->to_write][phil->var->gate_num];
	pthread_mutex_unlock(&phil->var->mess_m);
	ft_putnbr_str(time, &str);
	str_str(&str, " ms ");
	ft_putnbr_str(phil->num + 1, &str);
	str_str(&str, doing);
	pthread_mutex_unlock(mut);
	return (0);
}

static int	take_forks(t_philo *phil)
{
	pthread_mutex_lock(&phil->var->forks[phil->l_fork]);
	if (disp_mess(phil, " has taken a fork\n", \
		get_time() - phil->var->start, 18))
		return (1);
	pthread_mutex_lock(&phil->var->forks[phil->r_fork]);
	if (disp_mess(phil, " has taken a fork\n", \
		get_time() - phil->var->start, 18))
		return (1);
	pthread_mutex_unlock(&phil->var->mojna_jrat[phil->num]);
	return (0);
}

static void	put_forks(t_philo *phil)
{
	custom_sleep(phil->var->time_to_eat, phil->var->amount * 2);
	pthread_mutex_unlock(&phil->var->ya_poel[phil->num]);
	pthread_mutex_unlock(&phil->var->forks[phil->l_fork]);
	pthread_mutex_unlock(&phil->var->forks[phil->r_fork]);
}

static void	eating(t_philo	*phil)
{
	pthread_mutex_lock(&phil->var->eat_mutex[phil->num]);
	phil->lim = get_time() + phil->var->time_to_live;
	pthread_mutex_unlock(&phil->var->eat_mutex[phil->num]);
}

void	*philo_func(void *philo)
{
	t_philo	*phil;

	phil = philo;
	phil->begin = get_time();
	phil->lim = phil->begin + phil->var->time_to_live;
	if (phil->num % 2 == 1)
		pthread_mutex_lock(&phil->var->mojna_jrat[phil->num]);
	while (1)
	{
		take_forks(phil);
		pthread_mutex_unlock(&phil->var->mojna_jrat[phil->num]);
		eating(phil);
		if (disp_mess(phil, " is eating\n", get_time() - phil->var->start, 11))
			return ((void *)0);
		put_forks(phil);
		if (disp_mess(phil, " is sleeping\n", get_time() - phil->var->start, 13))
			return ((void *)0);
		custom_sleep(phil->var->time_to_sl, phil->var->amount * 2);
		if (disp_mess(phil, " is thinking\n", get_time() - phil->var->start, 13))
			return ((void *)0);
	}
	return ((void *)0);
}
