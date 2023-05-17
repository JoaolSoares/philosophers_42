/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:23:16 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/17 17:08:39 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	r_eat(t_philo *philo)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(philo->left_fork);
		printf("%li %i has taken a fork\n",timestamp(philo->init_time), philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%li %i has taken a fork\n",timestamp(philo->init_time), philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf("%li %i has taken a fork\n",timestamp(philo->init_time), philo->id);
		pthread_mutex_lock(philo->left_fork);
		printf("%li %i has taken a fork\n",timestamp(philo->init_time), philo->id);
	}
	printf("%li %i is eating\n", timestamp(philo->init_time), philo->id);
	philo->last_eat = timestamp(philo->init_time);
	philo->eat_count++;
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork); 
	pthread_mutex_unlock(philo->right_fork);
}

void	r_sleep(t_philo *philo)
{
	printf("%li %i is sleeping\n", timestamp(philo->init_time), philo->id);
	usleep(philo->time_to_sleep * 1000);
}

void	r_think(t_philo *philo)
{
	printf("%li %i is thinking\n", timestamp(philo->init_time), philo->id);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!*philo->death)		//talvez ter um monitor, que seja uma thread só para ficar monitorando
	{
		r_eat(philo);
		if (philo->max_eat != -1 && philo->eat_count >= philo->max_eat)
			break;
		r_sleep(philo);
		r_think(philo);
	}
	return ((void *)NULL);
}

		// if ((timestamp(philo->init_time) - philo->last_eat) >= philo->time_to_die)	//forma bem merda e não funciona	
		// {
		// 	printf("%li %i died\n", timestamp(philo->init_time), philo->id);
		// 	// philo->death++;
		// 	exit(0);
		// }