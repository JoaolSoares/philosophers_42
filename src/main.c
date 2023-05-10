/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:44:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/09 21:12:42 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*init_philo_stats(int tid, long int init_time, char *argv[])
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->tid = tid;
	philo->birth = init_time;
	philo->last_eat = 0;
	philo->eat_count = 0;
	if (!argv[5])
		philo->max_eat = -1;
	else
		philo->max_eat = ft_atoi(argv[5]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	return (philo);
}

int	arg_verification(int argc, char *argv[])
{
	int	i;

	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO, "Error! Wrong number of arguments...\n", 36);
		return (0);
	}
	i = 0;
	while (argv[++i])
		if (ft_atoi(argv[i]) < 0)
		{
			write(STDERR_FILENO, "Error! Negative arguments is forbidden...\n", 42);
			return (0);	
		}
	return (1);
}


int	main(int argc, char *argv[])
{
	pthread_t		tid[ft_atoi(argv[1])];
	t_philo			*table[ft_atoi(argv[1])];
	long int		init_time;
	long int		i;

	if (!arg_verification(argc, argv))
		return (1);

	init_time = timestamp(0);
	
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		table[i] = init_philo_stats(i, init_time, argv);
		if (pthread_create(&tid[i], NULL, &routine, (void *)table[i]) != 0)
			return (i + 10);
	}



	
	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		pthread_join(tid[i], NULL);
		pthread_detach(tid[i]);
		free(table[i]);
	}
	return (0);
}

