/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:25:11 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/25 15:49:43 by jlucas-s         ###   ########.fr       */
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

int	everyone_eat(t_data *data)
{
	int	id;

	if (data->philos[0]->max_eat == -1)
		return (FALSE);
	id = -1;
	while (++id < data->num_philos)
		if (data->philos[id]->eat_count < data->philos[id]->max_eat)
			return (FALSE);
	return (TRUE);
}

void	*monitor(void *arg)
{
	t_data	*data;
	int		id;

	data = (t_data *)arg;
	while (everyone_eat(data) == FALSE)
	{
		id = -1;
		while (++id < data->num_philos)
		{
			if ((timestamp(data->philos[id]->time->init) - \
				data->philos[id]->last_eat) > data->philos[id]->time->to_die && \
				data->philos[id]->eat_count != data->philos[id]->max_eat)
			{
				*data->philos[id]->had_deaths = TRUE;
				printf("%li %i died\n", timestamp(data->philos[id]->time->init), \
						data->philos[id]->id);
				return ((void *) NULL);
			}
		}
		usleep(5000);
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
