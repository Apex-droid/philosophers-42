/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:36:22 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 09:50:46 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

static char	*ft_strdup(const char *str)
{
	char			*v;
	unsigned long	i;

	i = ft_strlen(str) + 1;
	v = (char *)malloc(i);
	if (!v)
		return (0);
	while (*str != '\0')
		*v++ = *str++;
	*v = '\0';
	return (v - (i - 1));
}

static char	*ft_memandcount(int *y, int *x, int *j, char *u)
{
	while (*j != 0)
	{
		*j = *j / 10;
		*y = *y + 1;
	}
	if (*x < 0)
	{
		*y = *y + 2;
		*j = *x * (-1);
	}
	else
	{
		*y = *y + 1;
		*j = *x;
	}
	u = (char *)malloc(*y * sizeof(char));
	return (u);
}

static char	*ft_stringput(char *h, int *c, int *v, int *k)
{
	if (!h)
		return (NULL);
	*c = *c - 1;
	h[*c] = '\0';
	while (*v != 0)
	{
		*c = *c - 1;
		h[*c] = *v % 10 + '0';
		*v = *v / 10;
	}
	if (*k < 0)
		h[*c - 1] = '-';
	return (h);
}

char	*ft_itoa(int n)
{
	int		g;
	int		m;
	char	*t;

	g = 0;
	m = n;
	t = NULL;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	t = ft_memandcount(&g, &n, &m, t);
	t = ft_stringput(t, &g, &m, &n);
	return (t);
}
