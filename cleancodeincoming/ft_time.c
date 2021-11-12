/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:06:21 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/12 17:12:53 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_timediff(struct timeval t0, struct timeval t1)
{
	return ((t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec));
}

void	ft_wait(struct timeval start, int ttw, t_philo *philo)
{
	struct timeval	t;
	int				ret;

	ft_unlock_vars_mutex(philo);
	ret = gettimeofday(&t, NULL);
	while (ft_timediff(start, t) < ttw
		&& !ft_is_philo_dead(philo->last_meal, philo))
		ret = gettimeofday(&t, NULL);
	if (ft_is_philo_dead(philo->last_meal, philo))
	{
		ft_lock_vars_mutex(philo);
		/*ft_printf(" died", ft_timediff(philo->i_ttmp, t), (philo->id + 1),
			philo->vars->play);
		philo->vars->play = 0;
		philo->alive = 0;*/
		ft_died(philo, philo->id);
		ft_unlock_vars_mutex(philo);
	}
}
