/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:08:42 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/03 15:22:45 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	mon_status(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->status);
	if (r_get_time() - get_last_eat_time(philo) > philo->time_die)
	{
		philo->table->DEATH_WARN = DEAD;
		pthread_mutex_unlock(&philo->table->status);
		return (DEAD);
	}
	else if (philo->meals_eaten == philo->max_meals && \
	philo->full == 0)
	{
		philo->table->full_philos++;
		philo->full = 1;
	}
	if (philo->table->full_philos == philo->n_phs)
		philo->table->DEATH_WARN = FULL;
	i = philo->table->DEATH_WARN;
	pthread_mutex_unlock(&philo->table->status);
	return (i);
}

int	get_status(t_philo *philo)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philo->table->status);
	i = philo->table->DEATH_WARN;
	pthread_mutex_unlock(&philo->table->status);
	return (i);
}
