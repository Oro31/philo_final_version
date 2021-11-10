/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 18:55:32 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/10 17:04:24 by rvalton          ###   ########.fr       */
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
	int				use;
}				t_fork;

typedef struct s_vars {
	t_fork			*forks;
	pthread_mutex_t	mutex;
	struct timeval	initial_tmstmp;
	int				is_mutex_lock;
	int				nb_arg;
	int				ret;
	int				play;
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
	struct timeval	t;
	int				nb_eat;
	long			tte;
	long			tts;
	long			ttd;
	int				alive;
	int				id;
	int				ret;
}				t_philo;

int		ft_is_num(char *str);
int		ft_is_int(char *str);

void	ft_printf(char *msg, long tmstmp, int i, int play);

int		ft_atoi(const char *nptr);

long	ft_timediff(struct timeval t0, struct timeval t1);
void	ft_wait(struct timeval start, int ttw, t_philo *philo);

int		ft_is_philo_dead(struct timeval last_meal, t_vars *vars);
void	ft_philo_eat(t_philo *philo, int i, int j);
void	ft_philo_sleep(t_philo *philo, int i, int j);
void	ft_play_philo(t_philo *philo, int i, int j);
void	*ft_th_philo(void *p_data);

int		ft_create_philo_th(t_vars *vars, t_philo **philos);
int		ft_init_forks(t_vars *vars);
int		ft_init_vars(t_vars *vars, t_philo **philos, int argc, char **argv);
void	ft_init_philo(t_philo *philo);
void	ft_lock_unlock_vars_mutex(t_vars *vars, int opt);

#endif
