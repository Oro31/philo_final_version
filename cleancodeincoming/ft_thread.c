/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:08:17 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/12 17:28:38 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_is_philo_dead(struct timeval last_meal, t_philo *philo)
{
	struct timeval	t;
	int				ret;

	ret = gettimeofday(&t, NULL);
	if (ft_timediff(last_meal, t) > philo->ttd)
		return (1);
	return (0);
}

void	ft_philo_eat(t_philo *philo, int i, int j)
{
	ft_lock_forks_mutex(philo, i);
	/*philo->ret = gettimeofday(&philo->t, NULL);*/
	if (ft_is_philo_dead(philo->last_meal, philo))
	{
		ft_lock_vars_mutex(philo);
		ft_died(philo, i);
		ft_unlock_vars_mutex(philo);
	}
	else
	{
		ft_eating(philo, i);
		ft_wait(philo->last_meal, philo->tte, philo);
	}
}

void	ft_philo_sleep(t_philo *philo, int i, int j)
{
	ft_lock_vars_mutex(philo);
	if (philo->alive && philo->vars->play)
	{
		ft_sleeping(philo, i);
		ft_unlock_forks_mutex(philo, i);
		ft_wait(philo->t, philo->tts, philo);
		ft_lock_vars_mutex(philo);
		if (philo->alive && philo->vars->play)
			ft_thinking(philo, i);
		ft_unlock_vars_mutex(philo);
	}
	else
		ft_unlock_vars_mutex(philo);
}

void	ft_play_philo(t_philo *philo, int i, int j)
{
	if (ft_is_philo_dead(philo->last_meal, philo))
	{
		ft_died(philo, i);
		ft_unlock_vars_mutex(philo);

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
	while (philo->alive)
	{
		ft_lock_vars_mutex(philo);
		if (philo->vars->play == 0)
		{
			philo->alive = 0;
			ft_unlock_vars_mutex(philo);
		}
		else
		{
			ft_play_philo(philo, i, j);
		}
		philo->ret = gettimeofday(&philo->t, NULL);
		ft_wait(philo->t, 10, philo);
	}
	return (NULL);
}
