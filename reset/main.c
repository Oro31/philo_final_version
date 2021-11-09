/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:21:38 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/09 17:22:41 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;
	int		ret;

	if (argc < 2)
		return (0);
	vars.nb_philos = ft_atoi(argv[1]);
	vars.ttd = ft_atoi(argv[2]) * 1000;
	vars.tte = ft_atoi(argv[3]) * 1000;
	vars.tts = ft_atoi(argv[4]) * 1000;
	philos = malloc(sizeof(t_philo) * vars.nb_philos);
	vars.forks = malloc(sizeof(t_fork) * vars.nb_philos);
	ret = pthread_mutex_init(&vars.mutex, NULL);
	vars.is_mutex_lock = 0;
	vars.play = 1;
	i = -1;
	while (++i < vars.nb_philos)
	{
		vars.forks[i].use = 0;
		ret = pthread_mutex_init(&vars.forks[i].mutex, NULL);
	}
	i = -1;
	while (++i < vars.nb_philos)
	{
		philos[i].vars = &vars;
		philos[i].id = i;
		ret = pthread_create(&philos[i].th_philo, NULL,
			ft_th_philo, &philos[i]);
		if (ret)
			return (0);
	}
	i = -1;
	while (++i < vars.nb_philos)
		pthread_join(philos[i].th_philo, NULL);
	return (0);
}
