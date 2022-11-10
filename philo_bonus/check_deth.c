/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_deth.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:32:29 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 20:04:29 by ahelper          ###   ########.fr       */
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
	write(1, str, ft_strlen(str));
	return (0);
}

static int	deth(t_variables *var, int i)
{
	uint64_t	now_time;

	now_time = get_time();
	if ((unsigned long long)now_time > (unsigned long long)var->philos[i].lim)
	{
		sem_wait(var->write_m);
		if (disp_mess(&var->philos[i], \
		" is die\n\0", now_time - var->start))
		{
			sem_post(var->heart_attack);
			return (1);
		}
		sem_post(var->heart_attack);
		return (1);
	}
	return (0);
}

void	*check_thr(void *phil)
{
	t_philo	*phi;

	phi = phil;
	while (1)
	{
		usleep(1000);
		sem_wait(phi->eat_mutex);
		if (deth(phi->var, phi->num))
			return ((void *)1);
		sem_post(phi->eat_mutex);
	}
	return ((void *)0);
}
