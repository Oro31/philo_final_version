/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:08:17 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 19:19:43 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_is_philo_dead(struct timeval last_meal, t_vars *vars)
{
	struct timeval	t;
	int				ret;

	ret = gettimeofday(&t, NULL);
	if (ft_timediff(last_meal, t) > vars->ttd)
		return (1);
	return (0);
}

void	ft_philo_eat(t_philo *philo, int i, int j)
{	
	pthread_mutex_lock(&philo->vars->forks[i].mutex);
	philo->vars->forks[i].use = 1;
	pthread_mutex_lock(&philo->vars->forks[j].mutex);
	philo->vars->forks[j].use = 1;
	philo->vars->is_mutex_lock = 0;
	philo->ret = pthread_mutex_unlock(&philo->vars->mutex);
	philo->ret = gettimeofday(&philo->t, NULL);
	if (ft_is_philo_dead(philo->last_meal, philo->vars))
	{
		printf("%ld %d died\n", ft_timediff(philo->i_ttmp, philo->t) / 1000,
			(i + 1));
		philo->alive = 0;
		philo->vars->play = 0;
	}
	else
	{
		printf("%ld %d is eating\n", ft_timediff(philo->i_ttmp, philo->t)
			/ 1000, (i + 1));
		philo->ret = gettimeofday(&philo->last_meal, NULL);
		ft_wait(philo->last_meal, philo->tte, philo);
	}
}

void	ft_philo_sleep(t_philo *philo, int i, int j)
{
	if (philo->alive && philo->vars->play)
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		printf("%ld %d is sleeping\n", ft_timediff(philo->i_ttmp,
				philo->t) / 1000, (i + 1));
		pthread_mutex_unlock(&philo->vars->forks[i].mutex);
		philo->vars->forks[i].use = 0;
		pthread_mutex_unlock(&philo->vars->forks[j].mutex);
		philo->vars->forks[j].use = 0;
		ft_wait(philo->t, philo->tts, philo);
		if (philo->alive && philo->vars->play)
		{
			philo->ret = gettimeofday(&philo->t, NULL);
			printf("%ld %d is thinking\n", ft_timediff(philo->i_ttmp,
					philo->t) / 1000, (i + 1));
		}
	}
}

void	ft_play_philo(t_philo *philo, int i, int j)
{
	if (ft_is_philo_dead(philo->last_meal, philo->vars))
	{
		philo->ret = gettimeofday(&philo->t, NULL);
		printf("%ld %d died\n", ft_timediff(philo->i_ttmp, philo->t)
			/ 1000, (i + 1));
		philo->alive = 0;
		philo->vars->play = 0;
	}
	else if (philo->vars->forks[i].use == 0 && philo->vars->forks[j].use == 0)
	{
		ft_philo_eat(philo, i, j);
		ft_philo_sleep(philo, i, j);
	}
}

void	*ft_th_philo(void *p_data)
{
	t_philo	*philo;
	int		i;
	int		j;

	philo = (t_philo *)p_data;
	i = philo->id;
	j = (i + 1) % philo->vars->nb_philos;
	ft_init_philo(philo);
	while (philo->alive && philo->vars->play)
	{
		philo->ret = pthread_mutex_lock(&philo->vars->mutex);
		philo->vars->is_mutex_lock = 1;
		if (philo->vars->play)
			ft_play_philo(philo, i, j);
		if (philo->vars->is_mutex_lock)
			philo->ret = pthread_mutex_unlock(&philo->vars->mutex);
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_wait(philo->t, 10, philo);
	}
	return (NULL);
}
