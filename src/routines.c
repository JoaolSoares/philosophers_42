/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:23:16 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/09 21:29:26 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// void	eat(t_philo *philo)
// {
	
// }

// void	sleep(t_philo *philo)
// {
	
// }

void	*routine(void *ptr_philo)
{
	t_philo	*philo;

	philo = (t_philo *)ptr_philo;
	
	while (philo->eat_count <= philo->max_eat || philo->max_eat == -1)
	{
		// eat(philo);
		// sleep(philo);
	}
	
	return ((void *)philo);
}
