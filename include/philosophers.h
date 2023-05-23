/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:12:33 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/22 21:49:45 by jlucas-s         ###   ########.fr       */
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

//  STRUCTS  //
typedef enum t_bool
{
	FALSE,
	TRUE

}	t_bool;

typedef	struct s_time
{
	long int			init;
	int					to_die;
	int					to_sleep;
	int					to_eat;

}	t_time;

typedef	struct s_philo
{
	int					id;
	long int			birth;
	int 				eat_count;
	int					last_eat;
	int					max_eat;
	int					*had_deaths;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	struct s_time		*time;

}	t_philo;


//  FUNCTIONS  //
// Init
t_philo		**init_all_philos(int num_philos, pthread_mutex_t *forks, char *argv[]);

// threads
void		create_threads(pthread_t *tid, t_philo **philo, int num_threads);
void		*routine(void *arg);
void		*monitor(void *arg);

// Routines
void	r_eat(t_philo *philo);
void	r_sleep(t_philo *philo);
void	r_think(t_philo *philo);

//	Utils
int			ft_atoi(const char *nptr);
long int	timestamp(long int init_time);


#endif