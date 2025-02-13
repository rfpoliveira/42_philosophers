/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:10:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/02/04 10:10:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

size_t	r_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	r_usleep(size_t sleeptime)
{
	size_t	starting_time;

	starting_time = 0;
	starting_time = r_get_time();
	while ((r_get_time() - starting_time) < sleeptime)
		usleep(500);
}
