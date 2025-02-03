/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:52:49 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/22 16:55:26 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	r_isdigit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		i++;
	while(s[i])
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
		i++;
	}
	return (1);
}


int	r_atoi(const char *str)
{
	int	i;
	int	sig;
	int	res;

	res = 0;
	i = 0;
	sig = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		sig *= -1;
		i++;
	}
	if (str[i] == '+' && str[i - 1] != '+' && str[i - 1] != '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res *= 10;
		res += (str[i] - 48);
		i++;
	}
	return (res * sig);
}


size_t	r_get_time(void)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	r_usleep(size_t sleeptime)
{
	size_t starting_time;

	starting_time = 0;
	starting_time = r_get_time();
	while((r_get_time() - starting_time) < sleeptime)
		usleep(500);
}

void  print_msg(t_philo *philo, char *s)
{
	size_t time;

	time = 0;
	if (philo->table->DEATH_WARN != DEAD)
	{
		time = r_get_time() - philo->table->start_time;
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %i %s\n", time, philo->id, s);
		pthread_mutex_unlock(&philo->table->print);
	}
}
