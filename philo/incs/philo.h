/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:32:27 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/22 17:19:12 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/*============================================================================#
#                                 Libraries                                   #
#============================================================================*/
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

/*============================================================================#
#                                 macros                                   #
#============================================================================*/
# define ALIVE 1
# define DEAD 0
# define FULL 2
# define ERROR_MALLOC 3
# define PARSING_ERROR 4

# define FORK "has taken a fork"
# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIED "died"

/*============================================================================#
#                                 structs                                   #
#============================================================================*/
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meals_eaten;
	int				full;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			start_time;
	int				n_phs;
	int				max_meals;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	size_t			last_eat_time;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				n_phs;
	int				full_philos;
	int				death_warn;
	t_philo			*philos;
	pthread_t		monitor;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
	pthread_mutex_t	status;
	pthread_mutex_t	eating;
}	t_table;

/*============================================================================#
#								  functions                                   #
#============================================================================*/
//utils
int		r_atoi(const char *str);
int		r_isdigit(char *s);
void	print_msg(t_philo *philo, char *s);
int		r_strcmp(const char *s1, const char *s2);

//time utils
size_t	r_get_time(void);
void	r_usleep(size_t sleeptime);
size_t	get_last_eat_time(t_philo *philo);
void	set_last_eat_time(t_philo *philo);

//inicialize
void	ini_philos(t_table *table, int argc, char **info);
int		ini_table(t_table *table, int n_phs);
void	ini_forks(t_table *table);

//threads
int		create_threads(t_table *table);
int		get_status(t_philo *philo);
int		mon_status(t_philo *philo);

//activities
void	eat(t_philo *philo);
void	ph_sleep(t_philo *philo);
void	ph_think(t_philo *philo);

//handle memory
void	philo_free(t_table *table);

#endif
