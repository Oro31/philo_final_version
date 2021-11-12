/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:50:46 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/12 16:57:49 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_lock_vars_mutex(t_philo *philo)
{
	pthread_mutex_lock(&philo->vars->mutex);
	philo->vars->is_mutex_lock = 1;
}

void	ft_unlock_vars_mutex(t_philo *philo)
{
	philo->vars->is_mutex_lock = 0;
	pthread_mutex_unlock(&philo->vars->mutex);
}

void	ft_lock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	pthread_mutex_lock(&philo->vars->forks[i].mutex);
	philo->vars->forks[i].use = 1;
	pthread_mutex_lock(&philo->vars->forks[j].mutex);
	philo->vars->forks[j].use = 1;
}

void	ft_unlock_forks_mutex(t_philo *philo, int i)
{
	int	j;

	j = (i + 1) % philo->vars->nb_philos;
	philo->vars->forks[i].use = 0;
	pthread_mutex_lock(&philo->vars->forks[i].mutex);
	philo->vars->forks[j].use = 0;
	pthread_mutex_lock(&philo->vars->forks[j].mutex);
}
