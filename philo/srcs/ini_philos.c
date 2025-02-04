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

#include "../incs/philo.h"

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
	if (table->n_phs == 1)
	{
		philos[0].left_fork = NULL;
		return ;
	}
	philos[0].left_fork = &table->forks[philos[0].n_phs - 1];
	while (++i < table->n_phs)
	{
		if (philos[i].id % 2 == 0)
		{
			philos[i].right_fork = &table->forks[i];
			philos[i].left_fork = &table->forks[i - 1];
		}
		else
		{
			philos[i].right_fork = &table->forks[i - 1];
			philos[i].left_fork = &table->forks[i];
		}	
	}
}

void  ini_philos(t_table *table, int argc, char **info)
{
	int	i;
	t_philo *philos;

	i = 0;
	philos = table->philos;
	while (i < table->n_phs)
	{
		philos[i].n_phs = table->n_phs;
		philos[i].time_die = r_atoi(info[2]);
		philos[i].time_eat = r_atoi(info[3]);
		philos[i].time_sleep = r_atoi(info[4]);
		philos[i].start_time = r_get_time();
		philos[i].max_meals = -1;
		if (argc == 6)
			philos[i].max_meals = r_atoi(info[5]);
		philos[i].table = table;
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_eat_time = philos[i].start_time;
		philos[i].full = 0;
		i++;
	}
}

int	alloc_memory(t_table *table, int n_phs)
{
	table->philos = malloc(sizeof(t_philo) * n_phs);
	if (table->philos == NULL)
		return (ERROR_MALLOC);
	table->forks = malloc(sizeof(pthread_mutex_t) * n_phs);
	if (table->forks == NULL)
		return (free(table->philos), ERROR_MALLOC);
	return (0);
}

int  ini_table(t_table *table, int n_phs)
{
	table->n_phs = n_phs;
	table->DEATH_WARN = ALIVE;
	table->full_philos = 0;
	if (alloc_memory(table, n_phs) != 0)
		return (printf("Error allocating memory!\n"));
	pthread_mutex_init(&table->print, NULL);
	pthread_mutex_init(&table->status, NULL);
	pthread_mutex_init(&table->eating, NULL);
	return (0);
}

