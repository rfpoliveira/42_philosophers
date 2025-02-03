/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:39:11 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/27 12:40:21 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

int	eat(t_philo *philo)
{
	if (get_status(philo) == ALIVE)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, FORK);
		if (philo->n_phs == 1)
		{
			r_usleep(philo->time_die);
			return (1);
		}
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, FORK);
		print_msg(philo, EAT);
		r_usleep(philo->time_eat);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		if (philo->meals_eaten < philo->max_meals)
			philo->meals_eaten++;
		philo->last_eat_time = r_get_time();
	}
	return (0);
}

int	ph_sleep(t_philo *philo)
{
	if (get_status(philo) == ALIVE)
	{
		print_msg(philo, SLEEP);
		r_usleep(philo->time_sleep);
	}
	return (0);
}



