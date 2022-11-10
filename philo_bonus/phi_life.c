/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_life.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:13 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 19:40:33 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	disp_mess(t_philo *phil, char *doing, uint64_t time)
{
	char	str[65];
	char	*str1;

	str1 = str;
	ft_putnbr_str(time, &str1);
	str_str(&str1, " ms ");
	ft_putnbr_str(phil->num + 1, &str1);
	str_str(&str1, doing);
	sem_wait(phil->var->write_m);
	write(1, str, ft_strlen(str));
	sem_post(phil->var->write_m);
	return (0);
}

static int	take_forks(t_philo *phil)
{
	sem_wait(phil->var->forks);
	if (disp_mess(phil, " has taken a fork\n", \
		get_time() - phil->var->start))
		return (1);
	sem_wait(phil->var->forks);
	if (disp_mess(phil, " has taken a fork\n", \
		get_time() - phil->var->start))
		return (1);
	return (0);
}

static void	put_forks(t_philo *phil)
{
	custom_sleep(phil->var->time_to_eat, phil->var->amount * 2 );
	sem_post(phil->var->forks);
	sem_post(phil->var->forks);
}

static void	eating(t_philo	*phil)
{
	sem_wait(phil->eat_mutex);
	phil->lim = get_time() + phil->var->time_to_live;
	sem_post(phil->eat_mutex);
	sem_post(phil->ya_poel);
}

void	philo_func(void *philo)
{
	t_philo		*phil;
	pthread_t	check;

	phil = philo;
	phil->begin = get_time();
	phil->lim = phil->begin + phil->var->time_to_live;
	if (pthread_create(&check, NULL, &check_thr, philo))
		return ;
	while (1)
	{
		take_forks(phil);
		eating(phil);
		if (disp_mess(phil, " is eating\n", get_time() - phil->var->start))
			return ;
		put_forks(phil);
		if (disp_mess(phil, " is sleeping\n", get_time() - phil->var->start))
			return ;
		custom_sleep(phil->var->time_to_sl, phil->var->amount * 2);
		if (disp_mess(phil, " is thinking\n", get_time() - phil->var->start))
			return ;
	}
	return ;
}
