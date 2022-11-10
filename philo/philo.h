/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahelper <ahelper@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:56:15 by ahelper           #+#    #+#             */
/*   Updated: 2021/10/28 22:37:05 by ahelper          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include "pthread.h"
# include "unistd.h" 
# include <sys/time.h>
# include "stdlib.h"
# include "stdio.h"

struct	s_variables;

typedef struct s_philo
{
	int					num;
	int					l_fork;
	int					r_fork;
	int					is_eating;
	uint64_t			lim;
	uint64_t			begin;
	uint64_t			eat_time;
	uint64_t			sl_time;
	uint64_t			think_time;
	uint64_t			fork_time;
	struct s_variables	*var;

}			t_philo;

typedef struct s_variables
{
	uint64_t		time_to_eat;
	uint64_t		time_to_sl;
	uint64_t		time_to_live;
	uint64_t		start;
	int				amount;
	int				must_eat_count;
	int				eat_times;
	int				buff_count;
	int				buff_size;
	int				to_write;
	int				to_print;
	int				gate_num;
	int				death_flag;
	int				disp_flag;
	int				len[2];
	int				steward_d;
	pthread_mutex_t	mess_m;
	pthread_mutex_t	rasporyadok;
	pthread_mutex_t	heart_attack;
	pthread_mutex_t	print_m[2];
	pthread_mutex_t	mu;
	pthread_mutex_t	write_m;
	pthread_mutex_t	check_end;
	pthread_mutex_t	stop_end;
	pthread_t		print;
	pthread_t		t1;
	pthread_t		t2;
	pthread_t		t3;
	pthread_mutex_t	*stop;
	t_philo			*philos;
	pthread_t		*chairs;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*ya_poel;
	pthread_mutex_t	*mojna_jrat;
	pthread_mutex_t	*eat_mutex;
	pthread_mutex_t	*writex[2];
	char			*str;
	char			*buff[2];
}			t_variables;

int			parser(t_variables *vars, int argc, char **argv);
int			clean(t_variables *var);
void		*check_thr(void *vari);
void		*philo_func(void *philo);
int			var_init(t_variables *var);
void		*disp(void *vari);
int			deth_prep(t_philo *phil);
int			num_len(unsigned long long num);
void		ft_putnbr_str(uint64_t time, char **str);
void		str_str(char **str, char *str_past);
void		custom_sleep(uint64_t time, int k);
uint64_t	get_time(void);
void		*check_eat(void *vars);
void		gate_unlock(t_variables *var);
void		buff_update(t_variables *var, char **str);
int			kucha_mala(t_variables *var);
#endif 