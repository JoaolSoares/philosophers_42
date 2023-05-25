/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-s <jlucas-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 16:12:33 by jlucas-s          #+#    #+#             */
/*   Updated: 2023/05/24 23:30:29 by jlucas-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

//  INCLUDES  //
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

//  STRUCTS  //
typedef enum t_bool
{
	FALSE,
	TRUE
}	t_bool;

typedef struct s_time
{
	long int			init;
	int					to_die;
	int					to_sleep;
	int					to_eat;

}	t_time;

typedef struct s_philo
{
	pthread_t			tid;
	int					id;
	long int			birth;
	int					eat_count;
	int					last_eat;
	int					max_eat;
	int					*had_deaths;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_time				*time;

}	t_philo;

typedef struct s_data
{
	t_philo				**philos;
	pthread_mutex_t		*forks;
	pthread_t			tid_monitor;
	int					num_philos;

}	t_data;

//  FUNCTIONS  //
// Init and destroy
void		init_data(t_data *data, char *argv[]);
void		destroy_data(t_data *data);

// threads
void		create_threads(t_data *data);
void		*routine(void *arg);
void		*monitor(void *arg);

// Routines
void		r_eat(t_philo *philo);
void		r_sleep(t_philo *philo);
void		r_think(t_philo *philo);

//	Utils
int			ft_atoi(const char *nptr);
long int	timestamp(long int init_time);

#endif