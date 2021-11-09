/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 17:26:57 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				id;
	int				use;
}				t_fork;

typedef struct s_vars {
	t_fork			*forks;
	pthread_t		th_all;
	pthread_mutex_t	mutex;
	struct timeval	initial_tmstmp;
	int				is_mutex_lock;
	int				nb_arg;
	int				ret;
	int				play;
	int				set;
	int				id;
	int				nb_philos;
	long			ttd;
	long			tte;
	long			tts;
	int				nb_must_eat;
}				t_vars;

typedef struct s_philo {
	t_vars			*vars;
	pthread_t		th_philo;
	struct timeval	i_ttmp;
	struct timeval	last_meal;
	struct timeval	prev_t;
	struct timeval	t;
	int				nb_eat;
	long			tte;
	long			tts;
	long			ttd;
	int				alive;
	int				eat;
	int				feat;
	int				thi;
	int				sle;
	int				fsle;
	int				id;
	int				ret;
}				t_philo;

int		ft_atoi(const char *nptr);

long	ft_timediff(struct timeval t0, struct timeval t1);

void	ft_eat(t_vars *vars, int i);
void	ft_sleep(t_vars *vars, int i);
void	ft_check_for_dead(t_vars *vars);
void	ft_check_if_satiated(t_vars *vars);
void	*thread_monitoring(void *p_data);

void	ft_wait(struct timeval start, int ttw, t_philo *philo);
int		ft_is_philo_dead(struct timeval last_meal, t_vars *vars);
void	ft_philo_eat(t_philo *philo, int i, int j);
void	ft_philo_sleep(t_philo *philo, int i, int j);
void	*ft_th_philo(void *p_data);

void	ft_philo_eating(t_philo *philo);
void	ft_philo_sleeping(t_philo *philo);
void	*thread_philo(void *p_data);

void	ft_init_philo(t_philo *philo);

#endif
