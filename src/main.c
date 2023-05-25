/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:44:17 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/24 23:38:30 by jlucas-s         ###   ########.fr       */
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
		if (ft_atoi(argv[i]) <= 0)
		{
			write(STDERR_FILENO, \
			"Error! Negative or zeros arguments is forbidden...\n", 52);
			return (0);
		}
	}
	return (1);
}

int	one_philo(t_data *data)
{
	if (data->num_philos == 1)
	{
		printf("%li 1 has taken a fork\n", \
				timestamp(data->philos[0]->time->init));
		usleep(data->philos[0]->time->to_die * 1000);
		printf("%li 1 died\n", timestamp(data->philos[0]->time->init));
		return (0);
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (!arg_verification(argc, argv))
		return (1);
	data = (t_data *)malloc(sizeof(t_data));
	init_data(data, argv);
	if (one_philo(data))
		create_threads(data);
	destroy_data(data);
	return (0);
}
