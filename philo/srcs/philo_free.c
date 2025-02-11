/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:00:00 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/24 12:02:16 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

void	philo_free(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philos[0].n_phs)
		pthread_mutex_destroy(&table->forks[i]);
	pthread_mutex_destroy(&table->print);
	pthread_mutex_destroy(&table->status);
	pthread_mutex_destroy(&table->eating);
	free(table->philos);
	free(table->forks);
	free(table->thread_ph);
}
