/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:14:30 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/22 22:00:42 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_time	*init_time(char *args[])
{
	t_time		*time;

	time = (t_time *)malloc(sizeof(t_time));
	time->init = timestamp(0);
	time->to_die = ft_atoi(args[0]);
	time->to_eat = ft_atoi(args[1]);
	time->to_sleep = ft_atoi(args[2]);
	return (time);
}

t_philo	**init_all_philos(int num_philos, pthread_mutex_t *forks, char *argv[])
{
	t_philo			**philo;
	int				id;

	philo = (t_philo **)malloc(sizeof(t_philo *) * (num_philos + 1));
	id = -1;
	while (++id < num_philos)
	{
		philo[id] = (t_philo *)malloc(sizeof(t_philo));
		philo[id]->id = id + 1;
		philo[id]->time = init_time(argv + 2);
		philo[id]->birth = philo[id]->time->init;
		philo[id]->right_fork = &forks[id];
		philo[id]->left_fork = &forks[(id + 1) % num_philos];
		philo[id]->last_eat = 0;
		philo[id]->eat_count = 0;
		if (argv[5])
			philo[id]->max_eat = ft_atoi(argv[5]);
		else
			philo[id]->max_eat = -1;
	}
	philo[id] = NULL;
	return (philo);
}
