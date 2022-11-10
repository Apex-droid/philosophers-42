/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:31:25 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 21:45:07 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static const char	*ft_spaces(const char *st)
{
	while ((*st <= 13 && *st >= 9) || *st == 32)
	{
		st++;
	}
	return (st);
}

static int	ft_atoi(const char *str)
{
	unsigned long	m;
	int				y;

	y = 1;
	m = 0;
	str = ft_spaces(str);
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			y = -1;
		str++;
	}
	while (*str != '\0' && *str <= '9' && *str >= '0')
	{
		m = m * 10 + (*str - '0');
		str++;
	}
	if (m > 2147483648 && y == -1)
		return (0);
	if (m > 2147483647 && y == 1)
		return (-1);
	return ((int)m * y);
}

static int	arg_error(int argc)
{
	if (argc > 6)
	{
		write(1, "Error too much arguments\n", 25);
		return (1);
	}
	if (argc < 5)
	{
		write(1, "Error too few arguments\n", 24);
		return (1);
	}
	return (0);
}

static int	argneg(t_variables *vars, int argc, char **argv)
{
	if (argc == 6)
	{
		vars->must_eat_count = ft_atoi(argv[5]);
		if (ft_atoi(argv[5]) < 0)
		{
			write(1, "Error arg is not valid\n", 23);
			return (1);
		}
	}
	else
		vars->must_eat_count = -1;
	if (ft_atoi(argv[4]) <= 0 || \
	ft_atoi(argv[3]) <= 0 || ft_atoi(argv[2]) <= 0 \
	|| ft_atoi(argv[1]) <= 0 )
	{
		write(1, "Error arg is negative\n", 22);
		return (1);
	}
	return (0);
}

int	parser(t_variables *vars, int argc, char **argv)
{
	if (arg_error(argc))
		return (1);
	vars->amount = ft_atoi(argv[1]);
	if (vars->amount > 200)
	{
		write(1, "Error too many nerds\n", 21);
		return (1);
	}
	vars->time_to_live = ft_atoi(argv[2]);
	vars->time_to_eat = ft_atoi(argv[3]);
	vars->time_to_sl = ft_atoi(argv[4]);
	if (argneg(vars, argc, argv))
		return (1);
	if (vars->time_to_live < 60 || \
	vars->time_to_eat < 60 || vars->time_to_sl < 60)
	{
		write(1, "Error too short time\n", 21);
		return (1);
	}
	return (0);
}
