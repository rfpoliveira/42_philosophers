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

void  eat(t_philo *philo)
{
	if (get_status(philo) == ALIVE)
	{
		pthread_mutex_lock(philo->right_fork);
		print_msg(philo, FORK);
		if (philo->n_phs == 1)
		{
			r_usleep(philo->time_die);
			return ;
		}
		pthread_mutex_lock(philo->left_fork);
		print_msg(philo, FORK);
		set_last_eat_time(philo);
		print_msg(philo, EAT);
		r_usleep(philo->time_eat);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		if (philo->meals_eaten < philo->max_meals)
			philo->meals_eaten++;
	}
	return ;
}

void  ph_sleep(t_philo *philo)
{
	if (get_status(philo) == ALIVE)
	{
		print_msg(philo, SLEEP);
		r_usleep(philo->time_sleep);
	}
}

void  ph_think(t_philo *philo)
{
	if (get_status(philo) == ALIVE)
	{
		print_msg(philo, THINK);
	}
}



