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

void	routine_mon(t_table table)
{
	int		i;

	i = 0;
	while (42)
	{
		if (mon_status(&table.philos[i]) != ALIVE)
			break ;
		i++;
		if (i == table.n_phs)
			i = 0;
	}
	if (get_status(&table.philos[i]) == DEAD)
		print_msg(&table.philos[i], DIED);
}

void	*routine_ph(void *philo_arg)
{
	t_philo	*philo;

	philo = (t_philo *)philo_arg;
	philo->start_time = r_get_time();
	philo->last_eat_time = philo->start_time;
	if (philo->n_phs == 1)
	{
		print_msg(philo, FORK);
		r_usleep(philo->time_die);
		return (NULL);
	}
	if (philo->id % 2 != 0)
	{
		print_msg(philo, THINK);
		r_usleep(philo->time_eat);
	}
	while (get_status(philo) == ALIVE)
	{
		eat(philo);
		ph_sleep(philo);
		print_msg(philo, THINK);
	}
	return (NULL);
}

int	create_threads(pthread_t *thread_ph, t_philo *philos, int n_phs)
{
	int	i;

	i = -1;
	/*if (pthread_create(&table->monitor, NULL, &routine_mon, table) != 0)
		return (1);*/
	while (++i < n_phs)
	{
		if (pthread_create(&thread_ph[i], NULL, &routine_ph, \
		&philos[i]) != 0)
			return (1);
	}
	r_usleep(philos[0].time_eat - 10);
	routine_mon(*philos[0].table);
	i = -1;
	while (++i < n_phs)
	{
		if (pthread_join(thread_ph[i], NULL) != 0)
			return (1);
	}
	/*if (pthread_join(table->monitor, NULL) != 0)
		return (1);*/
	return (0);
}
