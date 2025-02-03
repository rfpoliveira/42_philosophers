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
	int	id;
	int meals_eaten;
	int	full;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
	size_t last_eat_time;
	struct s_table *table;
}	t_philo;

typedef	struct s_table
{
	size_t	time_die;
	size_t	time_eat;
	size_t	time_sleep;
	int		n_phs;
	int		full_philos;
	int		max_meals;
	int	DEATH_WARN;
	size_t	start_time;
	t_philo	*philos;
	pthread_t *philo_th;
	pthread_t monitor;
	pthread_mutex_t *forks;
	pthread_mutex_t print;
}	t_table;


/*============================================================================#
#								  functions                                   #
#============================================================================*/
//utils
int	r_atoi(const char *str);
int	r_isdigit(char *s);
size_t r_get_time(void);
void	r_usleep(size_t sleeptime);
void  print_msg(t_philo *philo, char *s);

//inicialize
void  ini_philos(t_table * table);
int  ini_table(int argc, char **info, t_table *table);
void  ini_forks(t_table *table);

//threads
int  create_threads(t_table *table);

//activities
int	eat(t_philo *philo);
int	ph_sleep(t_philo *philo);

//handle memory
void philo_free(t_table *table);

#endif
