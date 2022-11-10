/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:30:16 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 20:36:43 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pthr_func(t_variables *var)
{
	int	i;

	i = -1;
	if (pthread_create(&var->print, NULL, &disp, (void *)var))
		return (1);
	pthread_mutex_lock(&var->mu);
	var->start = get_time();
	while (++i < var->amount)
		if (pthread_create(&var->chairs[i], NULL, \
		&philo_func, (void *)&var->philos[i]))
			return (1);
	i = 0;
	while (i < var->amount - 1 && var->amount > 1)
	{
		pthread_mutex_lock(&var->mojna_jrat[i]);
		pthread_mutex_unlock(&var->mojna_jrat[i + 1]);
		i += 2;
	}
	if (pthread_create(&var->t3, NULL, &check_thr, (void *)var))
		return (1);
	if (var->must_eat_count != -1)
		if (pthread_create(&var->t2, NULL, &check_eat, (void *)(var)))
			return (1);
	return (0);
}

static void	*lead_thr(void *vari)
{
	t_variables	*var;

	var = vari;
	if (var_init(var) || pthr_func(var))
	{
		return ((void *)1);
	}
	pthread_mutex_lock(&var->heart_attack);
	return ((void *)0);
}

static void	steward_kill(t_variables *vars)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&vars->check_end);
	while (vars->steward_d)
	{	
		pthread_mutex_unlock(&vars->check_end);
		while (i < vars->amount)
			pthread_mutex_unlock(&vars->ya_poel[i++]);
		i = 0;
		pthread_mutex_lock(&vars->check_end);
	}
	pthread_mutex_lock(&vars->stop_end);
}

static void	end_wait(pthread_t *lead_thread, t_variables *vars, int argc)
{
	int	i;

	i = 0;
	pthread_join(*lead_thread, NULL);
	while (i < vars->amount)
	{
		pthread_mutex_lock(&vars->stop[i]);
		pthread_detach(vars->chairs[i++]);
	}
	i = 0;
	pthread_mutex_unlock(&vars->rasporyadok);
	if (argc == 6)
		steward_kill(vars);
	vars->disp_flag = 0;
	i = 0;
	vars->disp_flag = 0;
	while (i < vars->buff_size)
		pthread_mutex_unlock(&vars->writex[vars->to_print][i++]);
	pthread_join(vars->t3, NULL);
	pthread_join(vars->print, NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	lead_thread;
	t_variables	vars;
	int			i;

	i = 0;
	if (parser(&vars, argc, argv))
		return (1);
	if (pthread_create(&lead_thread, NULL, &lead_thr, (void *)(&vars)))
		return (1);
	end_wait(&lead_thread, &vars, argc);
	return (clean(&vars));
}
