/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:21:38 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 19:10:20 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;

	philos = NULL;
	if (!ft_init_vars(&vars, &philos, argc, argv))
		return (0);
	vars.is_mutex_lock = 0;
	vars.play = 1;
	if (!ft_init_forks(&vars))
		return (0);
	if (!ft_create_philo_th(&vars, &philos))
		return (0);
	i = -1;
	while (++i < vars.nb_philos)
		pthread_join(philos[i].th_philo, NULL);
	return (0);
}
