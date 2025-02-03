/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:55:41 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/22 17:19:20 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void  ini_forks(t_table *table)
{
	int	i;
	t_philo *philos;

	philos = table->philos;
	i = -1;
	while (++i < table->n_phs)
		pthread_mutex_init(&table->forks[i], NULL);
	i = 0;
	philos[0].right_fork = &table->forks[0];
	if (table->n_phs > 1)
		philos[0].left_fork = &table->forks[table->n_phs - 1];
	else
		philos[0].left_fork = NULL;
	while (++i < table->n_phs)
	{
		philos[i].right_fork = &table->forks[i];
		philos[i].left_fork = &table->forks[i - 1];
	}
}

void  ini_philos(t_table *table)
{
	int	i;
	t_philo *philos;

	i = 0;
	philos = table->philos;
	while (i < table->n_phs)
	{
		philos[i].table = table;
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_eat_time = table->start_time;
		philos[i].full = 0;
		i++;
	}
}

int	alloc_memory(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_phs);
	if (table->philos == NULL)
		return (ERROR_MALLOC);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_phs);
	if (table->forks == NULL)
		return (free(table->philos), ERROR_MALLOC);
	table->philo_th = malloc(sizeof(pthread_t) * table->n_phs);
	if (table->philo_th == NULL)
		return(free(table->philos), free(table->forks), ERROR_MALLOC);
	return (0);
}

int  ini_table(int argc, char **info, t_table *table)
{
	table->n_phs = r_atoi(info[1]);
	table->time_die = r_atoi(info[2]);
	table->time_eat = r_atoi(info[3]);
	table->time_sleep = r_atoi(info[4]);
	table->max_meals = -1;
	if (argc == 6)
		table->max_meals = r_atoi(info[5]);
	table->start_time = r_get_time();
	table->DEATH_WARN = ALIVE;
	table->full_philos = 0;
	if (alloc_memory(table) != 0)
		return (printf("Error allocating memory!\n"));
	pthread_mutex_init(&table->print, NULL);
	return (0);
}

