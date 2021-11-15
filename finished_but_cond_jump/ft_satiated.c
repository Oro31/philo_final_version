/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_satiated.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 14:13:31 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/15 14:23:02 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_satiated(t_philo *philo)
{
	if (philo->is_must_eat)
	{
		philo->nb_eat++;
		if (philo->nb_eat == philo->nb_must_eat)
			philo->vars->nb_philos_satiated++;
		if (philo->vars->nb_philos_satiated == philo->vars->nb_philos)
		{
			philo->alive = 0;
			philo->vars->play = 0;
		}
	}
}
