/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 12:21:38 by rvalton           #+#    #+#             */
/*   Updated: 2021/11/10 13:50:38 by rvalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_exit(t_philo **philos, t_vars *vars, int code)
{
	int	i;

	if (code == 0)
		return (0);
	free(vars->forks);
	free(philos[0]);
	vars->ret = pthread_mutex_destroy(&vars->mutex);
	if (code == 1)
		printf("Error : failed initialising forks mutex\n");
	else
	{
		i = -1;
		while (++i < vars->nb_philos)
			vars->ret = pthread_mutex_destroy(&vars->forks[i].mutex);
		if (code == 2)
			printf("Error : failed creating philos thread\n");
		else if (code == 3)
			printf("Error : failed joining thread\n");
	}
	return (0);
}

static int	ft_handle_argv(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
	{
		if (!ft_is_int(argv[i]))
			return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_philo	*philos;
	int		i;

	philos = NULL;
	if (!ft_handle_argv(argc, argv))
		return (0);
	if (!ft_init_vars(&vars, &philos, argc, argv))
		return (ft_exit(&philos, &vars, 0));
	vars.is_mutex_lock = 0;
	vars.play = 1;
	if (!ft_init_forks(&vars))
		return (ft_exit(&philos, &vars, 1));
	if (!ft_create_philo_th(&vars, &philos))
		return (ft_exit(&philos, &vars, 2));
	i = -1;
	while (++i < vars.nb_philos)
	{
		vars.ret = pthread_join(philos[i].th_philo, NULL);
		if (vars.ret)
			return (ft_exit(&philos, &vars, 3));
	}
	return (ft_exit(&philos, &vars, 4));
}
