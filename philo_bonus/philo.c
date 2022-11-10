/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:30:16 by ahelper           #+#    #+#             */
/*   Updated: 2021/11/05 18:11:17 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_process(t_variables *var)
{
	int			i;
	t_philo		*philo;

	i = 0;
	while (i < var->amount)
	{
		philo = &var->philos[i];
		var->philos[i].pid = fork();
		if (var->philos[i].pid < 0)
			return (1);
		else if (var->philos[i].pid == 0)
		{
			philo_func(&var->philos[i]);
			exit(0);
		}
		i++;
	}
	return (0);
}

static int	pthr_func(t_variables *var)
{
	int	i;

	i = 0;
	var->start = get_time();
	if (start_process(var))
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
		return ((void *)1);
	sem_wait(var->heart_attack);
	if (var->must_eat_count != -1)
	{
		steward_kill(var);
	}
	return ((void *)0);
}

static void	end_wait(pthread_t *lead_thread, t_variables *vars)
{
	int	i;

	i = 0;
	pthread_join(*lead_thread, NULL);
	while (i < vars->amount)
	{
		kill(vars->philos[i].pid, SIGKILL);
		i++;
	}
	sem_close(vars->forks);
	sem_unlink("\f");
	i = 0;
	sem_post(vars->rasporyadok);
	i = 0;
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
	end_wait(&lead_thread, &vars);
	return (clean(&vars));
}
