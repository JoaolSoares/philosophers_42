/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:23:16 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/24 21:11:15 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(long int time, t_philo *philo, char *str)
{
	if (*philo->had_deaths == FALSE)
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
	philo->last_eat = timestamp(philo->time->init);
	print_action(timestamp(philo->time->init), philo, "has taken a fork");
	print_action(timestamp(philo->time->init), philo, "has taken a fork");
	print_action(timestamp(philo->time->init), philo, "is eating");
	usleep(philo->time->to_eat * 1000);
	philo->eat_count++;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	r_sleep(t_philo *philo)
{
	print_action(timestamp(philo->time->init), philo, "is sleeping");
	usleep(philo->time->to_sleep * 1000);
}

void	r_think(t_philo *philo)
{
	print_action(timestamp(philo->time->init), philo, "is thinking");
}
