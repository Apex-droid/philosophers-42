/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_ut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:30:44 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 19:39:52 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	steward_kill(t_variables *vars)
{
	int	i;

	i = 0;
	sem_wait(vars->check_end);
	while (vars->steward_d)
	{
		vars->death_flag = 0;
		sem_post(vars->check_end);
		while (i < vars->amount)
			sem_post(vars->philos[i++].ya_poel);
		i = 0;
		sem_wait(vars->check_end);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*u;
	size_t	y;
	size_t	x;

	if (!s1 || !s2)
		return (NULL);
	y = ft_strlen(s2);
	x = ft_strlen(s1);
	u = (char *)malloc(x + y + 1);
	if (!u)
		return (NULL);
	u[y + x] = '\0';
	while (y--)
		u[x + y] = s2[y];
	while (x--)
		u[x] = s1[x];
	return (u);
}

uint64_t	get_time(void)
{
	static struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000);
}

void	custom_sleep(uint64_t time, int k)
{
	uint64_t	i;

	i = get_time();
	while (get_time() < i + time)
	{
		usleep(k);
	}
}
