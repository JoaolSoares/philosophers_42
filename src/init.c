/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 23:14:30 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/24 21:30:43 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_time	*init_time(char *args[])
{
	t_time		*time;

	time = malloc(sizeof(t_time));
	time->init = timestamp(0);
	time->to_die = ft_atoi(args[0]);
	time->to_eat = ft_atoi(args[1]);
	time->to_sleep = ft_atoi(args[2]);
	return (time);
}

void	init_data(t_data *data, char *argv[])
{
	int	id;

	data->num_philos = ft_atoi(argv[1]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	id = -1;
	while (++id < data->num_philos)
		pthread_mutex_init(&data->forks[id], NULL);
	data->philos = malloc(sizeof(t_philo *) * data->num_philos);
	id = -1;
	while (++id < data->num_philos)
	{
		data->philos[id] = malloc(sizeof(t_philo));
		data->philos[id]->id = id + 1;
		data->philos[id]->time = init_time(argv + 2);
		data->philos[id]->birth = data->philos[id]->time->init;
		data->philos[id]->right_fork = &data->forks[id];
		data->philos[id]->left_fork = &data->forks[(id + 1) % data->num_philos];
		data->philos[id]->last_eat = 0;
		data->philos[id]->eat_count = 0;
		if (argv[5])
			data->philos[id]->max_eat = ft_atoi(argv[5]);
		else
			data->philos[id]->max_eat = -1;
	}
}

void	destroy_data(t_data *data)
{
	int	id;

	id = -1;
	while (++id < data->num_philos)
	{
		free(data->philos[id]->time);
		free(data->philos[id]);
	}
	free(data->philos);
	free(data->forks);
	free(data);
}
