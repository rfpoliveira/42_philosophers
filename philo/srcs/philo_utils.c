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

#include "../incs/philo.h"

int	r_isdigit(char *s)
{
	int	i;

	i = 0;
	if (s[0] == '+')
		i++;
	while (s[i])
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

void	print_msg(t_philo *philo, char *s)
{
	size_t	time;

	time = 0;
	if (philo->table->death_warn == ALIVE)
	{
		pthread_mutex_lock(&philo->table->print);
		time = r_get_time() - philo->table->start_time;
		printf("%ld %i %s\n", time, philo->id, s);
		pthread_mutex_unlock(&philo->table->print);
	}
	else if (r_strcmp(s, "died") == 0)
	{
		time = r_get_time() - philo->table->start_time;
		pthread_mutex_lock(&philo->table->print);
		printf("%ld %i %s\n", time, philo->id, s);
		pthread_mutex_unlock(&philo->table->print);
	}
}

int	r_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*temps1;
	unsigned char	*temps2;

	temps1 = (unsigned char *)s1;
	temps2 = (unsigned char *)s2;
	i = 0;
	while (temps1[i] || temps2[i])
	{
		if (temps1[i] != temps2[i])
			return (temps1[i] - temps2[i]);
		i++;
	}
	return (0);
}
