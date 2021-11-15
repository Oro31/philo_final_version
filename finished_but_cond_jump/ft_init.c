/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:15:59 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/15 15:13:31 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_init_philo(t_philo *philo)
{
	if (philo->vars->nb_arg == 6)
	{
		philo->nb_must_eat = philo->vars->nb_must_eat;
		philo->is_must_eat = 1;
	}
	else
		philo->is_must_eat = 0;
	philo->nb_eat = 0;
	philo->ttd = philo->vars->ttd;
	philo->tte = philo->vars->tte;
	philo->tts = philo->vars->tts;
	philo->i_ttmp = philo->vars->initial_tmstmp;
}

int	ft_init_vars(t_vars *vars, t_philo **philos, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (argc == 6)
		vars->nb_must_eat = ft_atoi(argv[5]);
	vars->nb_philos = ft_atoi(argv[1]);
	vars->ttd = ft_atoi(argv[2]) * 1000;
	vars->tte = ft_atoi(argv[3]) * 1000;
	vars->tts = ft_atoi(argv[4]) * 1000;
	philos[0] = malloc(sizeof(t_philo) * vars->nb_philos);
	if (!philos[0])
		return (0);
	vars->forks = malloc(sizeof(t_fork) * vars->nb_philos);
	if (!vars->forks)
	{
		free(philos[0]);
		return (0);
	}
	vars->ret = pthread_mutex_init(&vars->mutex, NULL);
	if (vars->ret)
	{
		free(philos[0]);
		free(vars->forks);
		return (0);
	}
	return (1);
}

int	ft_init_forks(t_vars *vars)
{
	int	i;
	int	ret;

	i = -1;
	while (++i < vars->nb_philos)
	{
		vars->forks[i].use = 0;
		ret = pthread_mutex_init(&vars->forks[i].mutex, NULL);
		if (ret)
		{
			while (--i >= 0)
			{
				ret = pthread_mutex_destroy(&vars->forks[i].mutex);
				if (ret)
					return (0);
			}
		}
	}
	return (1);
}

int	ft_create_philo_th(t_vars *vars, t_philo **philos)
{
	int	i;
	int	ret;

	ret = gettimeofday(&vars->initial_tmstmp, NULL);
	i = -1;
	while (++i < vars->nb_philos)
	{
		philos[0][i].vars = vars;
		philos[0][i].id = i;
		ft_init_philo(&philos[0][i]);
		ret = pthread_create(&philos[0][i].th_philo, NULL, ft_th_philo,
				&philos[0][i]);
		if (ret)
			return (0);
	}
	return (1);
}
