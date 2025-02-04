/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:15:10 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/24 11:15:43 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

/*int	monitor_util(t_table *table, int i)
{
	
	if (table->philos[i].meals_eaten == table->max_meals && \
			table->philos[i].full == 0)
	{		
		table->full_philos++;
		table->philos[i].full = 1;
	}	
	if (table->full_philos == table->n_phs)
	{	
		get_status(table->philos[0], FULL);
		return (1);
	}
	return (0);
}
*/
void *routine_mon(void	*table_arg)
{
	t_table *table;
	int	i;

	i = 0;
	table = (t_table *)table_arg;
	while (42)
	{
	if (mon_status(&table->philos[i]) != ALIVE)
		break ;
	i++;
	if (i == table->n_phs)
		i = 0;
	}
	if (get_status(&table->philos[i]) == DEAD)
		print_msg(&table->philos[i], DIED);
	return (NULL);
}


void  *routine_ph(void	*philo_arg)
{
	t_philo *philo;

	philo = (t_philo *)philo_arg;
	if (philo->id % 2 != 0)
	{
		print_msg(philo, THINK);
		r_usleep(philo->time_eat);
	}
	while (get_status(philo) == ALIVE)
	{
		eat(philo);
		ph_sleep(philo);
		ph_think(philo);
	}
	return (NULL);
}

int  create_threads(t_table *table)
{
	int i;

	i = -1;
	if (pthread_create(&table->monitor, NULL, &routine_mon, table) != 0)
		return (1);
	while (++i < table->philos[0].n_phs)
	{
		if (pthread_create(&table->philos[i].thread, NULL, &routine_ph, &table->philos[i]) != 0)
			return (1);
	}
	i = -1;
	while (++i < table->philos[0].n_phs)
	{
		if (pthread_join(table->philos[i].thread, NULL) != 0)
			return (1);
	}
	if (pthread_join(table->monitor, NULL)!= 0)
		return (1);
	return (0);
}
