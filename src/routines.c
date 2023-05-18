/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:23:16 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/18 20:23:23 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long int time, t_philo *philo, char *str)
{
	if (!*philo->death)
		printf("%li %i %s\n", time, philo->id, str);
}

void	r_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
	philo->last_eat = timestamp(philo->init_time);
	print_action(timestamp(philo->init_time), philo, "has taken a fork left");
	print_action(timestamp(philo->init_time), philo, "has taken a fork right");
	print_action(timestamp(philo->init_time), philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	r_sleep(t_philo *philo)
{
	print_action(timestamp(philo->init_time), philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

void	r_think(t_philo *philo)
{
	print_action(timestamp(philo->init_time), philo, "is thinking");
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!*philo->death)
	{
		r_eat(philo);
		if (philo->max_eat != -1 && philo->eat_count >= philo->max_eat)
			return ((void *)NULL);
		r_sleep(philo);
		r_think(philo);
	}
	return ((void *)NULL);
}
