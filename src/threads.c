/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:25:11 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/24 21:30:28 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*philo->had_deaths == FALSE)
	{
		r_eat(philo);
		if (philo->max_eat != -1 && philo->eat_count >= philo->max_eat)
			return ((void *) NULL);
		r_sleep(philo);
		r_think(philo);
	}
	return ((void *) NULL);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		id;

	data = (t_data *)arg;
	while (1)
	{
		id = -1;
		while (++id < data->num_philos)
		{
			if ((timestamp(data->philos[id]->time->init) - \
				data->philos[id]->last_eat) > data->philos[id]->time->to_die)
			{
				*data->philos[id]->had_deaths = TRUE;
				printf("%li %i died\n", timestamp(data->philos[id]->time->init), \
						data->philos[id]->id);
				return ((void *) NULL);
			}
		}
		usleep(50000);
	}
	return ((void *) NULL);
}

void	create_threads(t_data *data)
{
	int	id;
	int	p_deaths;

	p_deaths = FALSE;
	id = -1;
	while (++id < data->num_philos)
	{
		data->philos[id]->had_deaths = &p_deaths;
		pthread_create(&data->philos[id]->tid, NULL, routine, \
		(void *)data->philos[id]);
	}
	pthread_create(&data->tid_monitor, NULL, monitor, (void *)data);
	id = -1;
	while (++id < data->num_philos)
		pthread_join(data->philos[id]->tid, NULL);
	pthread_join(data->tid_monitor, NULL);
}
