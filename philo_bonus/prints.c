/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:30:35 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 05:22:24 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	str_str(char **str, char *str_past)
{
	while (*str_past)
	{
		**str = *str_past;
		str_past++;
		++*str;
	}
	**str = '\0';
}

void	ft_putnbr_str(uint64_t time, char **str)
{
	int	num;

	num = time % 10;
	if (time >= 10)
		ft_putnbr_str(time / 10, str);
	**str = num + '0';
	++*str;
}

int	num_len(unsigned long long num)
{
	int	i;

	if (num == 0)
		i = 1;
	else
		i = 0;
	while (num != 0)
	{
		num = num / 10;
		i++;
	}
	return (i);
}
