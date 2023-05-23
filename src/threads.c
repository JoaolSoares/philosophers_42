/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 00:25:11 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/22 22:14:20 by jlucas-s         ###   ########.fr       */
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
	t_philo	**philo;
	int		id;

	philo = (t_philo **)arg;
	while (1)
	{
		id = -1;
		while (philo[++id])
		{
			if ((timestamp(philo[id]->time->init) - philo[id]->last_eat) > philo[id]->time->to_die)
			{
				*philo[id]->had_deaths = TRUE;
				printf("%li %i died\n", timestamp(philo[id]->time->init), philo[id]->id);
				return ((void *) NULL);
			}
		}
		usleep(5000);
	}
	return ((void *) NULL);
}

void	create_threads(pthread_t *tid, t_philo **philo, int num_threads)
{
	int	id;
	int	p_deaths;

	p_deaths = FALSE;
	id = -1;
	while (++id < num_threads)
	{
		philo[id]->had_deaths = &p_deaths;
		pthread_create(&tid[id], NULL, routine, (void *)philo[id]);
	}
	pthread_create(&tid[id], NULL, monitor, (void *)philo);
}
