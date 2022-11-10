/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_ut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:30:44 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/27 12:19:40 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
