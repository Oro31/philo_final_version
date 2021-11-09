/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:15:59 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 17:27:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_init_philo(t_philo *philo)
{
	philo->ttd = philo->vars->ttd;
	philo->tte = philo->vars->tte;
	philo->tts = philo->vars->tts;
	philo->ret = gettimeofday(&philo->i_ttmp, NULL);
	philo->ret = gettimeofday(&philo->last_meal, NULL);
	philo->alive = 1;
}
