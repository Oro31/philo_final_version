/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:06:21 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 19:20:01 by rvalton          ###   ########.fr       */
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

	ret = gettimeofday(&t, NULL);
	while (ft_timediff(start, t) < ttw
		&& !ft_is_philo_dead(philo->last_meal, philo->vars))
		ret = gettimeofday(&t, NULL);
	if (ft_is_philo_dead(philo->last_meal, philo->vars))
	{
		printf("%ld %d died\n", ft_timediff(philo->i_ttmp, t) / 1000,
			(philo->id + 1));
		philo->alive = 0;
		philo->vars->play = 0;
	}
}
