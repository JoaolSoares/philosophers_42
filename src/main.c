/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:44:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/18 20:20:56 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	**init_all_philos(int num_philos, pthread_mutex_t *forks, char *argv[])
{
	t_philo			**table;
	long int		init_time;
	int				id;
	int				num_deaths;

	table = (t_philo **)malloc(sizeof(t_philo) * num_philos);
	init_time = timestamp(0);
	num_deaths = 0;
	id = -1;
	while (++id < num_philos)
	{
		table[id] = (t_philo *)malloc(sizeof(t_philo));
		table[id]->id = id + 1;
		table[id]->right_fork = &forks[id];
		table[id]->left_fork = &forks[(id + 1) % num_philos];
		table[id]->init_time = init_time;
		table[id]->birth = init_time;
		table[id]->last_eat = 0;
		table[id]->eat_count = 0;
		table[id]->time_to_die = ft_atoi(argv[2]);
		table[id]->time_to_eat = ft_atoi(argv[3]);
		table[id]->time_to_sleep = ft_atoi(argv[4]);
		table[id]->death = &num_deaths;
		if (!argv[5])
			table[id]->max_eat = -1;
		else
			table[id]->max_eat = ft_atoi(argv[5]);
	}
	return (table);
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
			if ((timestamp(philo[id]->init_time) - philo[id]->last_eat) >= philo[id]->time_to_die)
			{
				*philo[id]->death = 1;
				printf("%li %i died\n", timestamp(philo[id]->init_time), philo[id]->id);
				return ((void *)NULL);
			}
		}
		usleep(5000);
	}

	return ((void *)NULL);
}

int	main(int argc, char *argv[])
{
	pthread_t		tid[ft_atoi(argv[1]) + 1];
	pthread_mutex_t	forks[ft_atoi(argv[1])];
	t_philo			**table;
	long int		id;

	if (!arg_verification(argc, argv))
		return (1);
	id = -1;
	while (++id < ft_atoi(argv[1]))
		pthread_mutex_init(&forks[id], NULL);
	table = init_all_philos(ft_atoi(argv[1]), forks, argv);
	id = -1;
	while (++id < ft_atoi(argv[1]))
	{
		if (pthread_create(&tid[id], NULL, routine, (void *)table[id]) != 0)
			return (id + 10);
	}
	if (pthread_create(&tid[ft_atoi(argv[1])], NULL, monitor, (void *)table) != 0)
			return (101);
	id = -1;
	while (++id < ft_atoi(argv[1]))
	{
		pthread_join(tid[id], NULL);
		pthread_detach(tid[id]);
		free(table[id]);
	}
	free(table);
	return (0);
}
