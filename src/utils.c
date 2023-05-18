/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:35:15 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/18 20:09:06 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int	is_neg;
	int	i;
	int	n;

	is_neg = 1;
	i = 0;
	if (!nptr)
		return (0);
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || nptr[i] == ' ')
		i++;
	if (nptr[i] == '-')
		is_neg = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		++i;
	n = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		n = (n * 10) + nptr[i] - '0';
		++i;
	}
	return (n * is_neg);
}

long int	timestamp(long int init_time)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (init_time == 0)
		return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	else
		return ((tv.tv_sec * 1000 + tv.tv_usec / 1000) - init_time);
}
