/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:12:33 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/09 20:23:37 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//  INCLUDES  //
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

//  DEFINES  //


//  STRUCTS  //
typedef struct s_philo
{
	int			tid;
	long int	birth;
	int			last_eat;
	int 		eat_count;
	int			max_eat;
	int			time_to_die;
	int			time_to_sleep;
	int			time_to_eat;

}	t_philo;


//  FUNCTIONS  //
//	utils
int			ft_atoi(const char *nptr);
long int	timestamp(long int init_time);

// routine
void		*routine(void *i);


#endif