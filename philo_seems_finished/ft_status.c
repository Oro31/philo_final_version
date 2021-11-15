/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_status.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:59:42 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/15 13:14:27 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_sleeping(t_philo *philo, int i)
{
	philo->ret = gettimeofday(&philo->t, NULL);
	ft_printf("is sleeping", ft_timediff(philo->i_ttmp, philo->t), (i + 1),
		philo->vars->play);
}

void	ft_eating(t_philo *philo, int i)
{
	philo->ret = gettimeofday(&philo->last_meal, NULL);
	ft_printf("is eating", ft_timediff(philo->i_ttmp, philo->last_meal),
		(i + 1), philo->vars->play);
}

void	ft_thinking(t_philo *philo, int i)
{
	philo->ret = gettimeofday(&philo->t, NULL);
	ft_printf("is thinking", ft_timediff(philo->i_ttmp, philo->t), (i + 1),
		philo->vars->play);
}

void	ft_died(t_philo *philo, int i)
{
	philo->ret = gettimeofday(&philo->t, NULL);
	ft_printf("died", ft_timediff(philo->i_ttmp, philo->t), (i + 1),
		philo->vars->play);
	philo->alive = 0;
	philo->vars->play = 0;
}
