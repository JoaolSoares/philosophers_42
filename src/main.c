/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:44:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/23 15:01:25 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	{
		if (ft_atoi(argv[i]) < 0)
		{
			write(STDERR_FILENO, \
			"Error! Negative arguments is forbidden...\n", 42);
			return (0);
		}
	}
	return (1);
}
// fazer caso para um philo só
// tem um erro quando faz com ponteiro normal, e não um tamanho ja definido não sei pq
int	main(int argc, char *argv[])
{
	int					id;
	t_philo				**philo;
	// pthread_mutex_t		*forks;
	// pthread_t			*tid;
	pthread_mutex_t		forks[ft_atoi(argv[1])];
	pthread_t			tid[ft_atoi(argv[1]) + 1];

	if (!arg_verification(argc, argv))
		return (1);
	// forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	// tid = (pthread_t *)malloc(sizeof(pthread_t) * (ft_atoi(argv[1]) + 1));
	id = -1;
	while (++id < ft_atoi(argv[1]))
		pthread_mutex_init(&forks[id], NULL);
	philo = init_all_philos(ft_atoi(argv[1]), forks, argv);
	create_threads(tid, philo, ft_atoi(argv[1]));
	id = -1;
	while (++id < ft_atoi(argv[1]))
	{
		pthread_join(tid[id], NULL);
		pthread_detach(tid[id]);
		free(philo[id]->time);
		free(philo[id]);
	}
	pthread_join(tid[id], NULL);
	pthread_detach(tid[id]);
	// free(tid);
	// free(forks);
	free(philo);
	return (0);
}
