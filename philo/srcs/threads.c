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

int	mon_status(t_philo *philo)
{
	int	i;

	i = 0;
	if (r_get_time() - philo->last_eat_time > (size_t)philo->table->time_die)
	{
		philo->table->death_warn = DEAD;
		return (DEAD);
	}
	else if (philo->meals_eaten == philo->table->max_meals && \
	philo->full == 0)
	{
		philo->table->full_philos++;
		philo->full = 1;
	}
	if (philo->table->full_philos == philo->table->n_phs)
		philo->table->death_warn = FULL;
	i = philo->table->death_warn;
	return (i);
}

void	routine_mon(t_table *table)
{
	int		i;

	i = 0;
	while (42)
	{
		if (mon_status(&table->philos[i]) != ALIVE)
			break ;
		i++;
		if (i == table->n_phs)
			i = 0;
	}
	if (table->death_warn == DEAD)
		print_msg(&table->philos[i], DIED);
}

void	*routine_ph(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	pthread_mutex_lock(&philo->table->status);
	pthread_mutex_unlock(&philo->table->status);
	philo->last_eat_time = philo->table->start_time;
	if (philo->table->n_phs == 1)
	{
		print_msg(philo, FORK);
		r_usleep(philo->table->time_die);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		print_msg(philo, THINK);
		r_usleep(philo->table->time_eat);
	}
	while (philo->table->death_warn == ALIVE)
	{
		eat(philo);
		ph_sleep(philo);
		print_msg(philo, THINK);
	}
	return (NULL);
}

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&table->status);
	while (++i < table->n_phs)
	{
		if (pthread_create(&table->thread_ph[i], NULL, &routine_ph, \
		&table->philos[i]) != 0)
			return (1);
	}
	table->start_time = r_get_time();
	pthread_mutex_unlock(&table->status);
	r_usleep(table->time_eat - 10);
	routine_mon(table);
	i = -1;
	while (++i < table->n_phs)
	{
		if (pthread_join(table->thread_ph[i], NULL) != 0)
			return (1);
	}
	return (0);
}
