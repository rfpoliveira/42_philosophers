/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:46:05 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/22 17:02:36 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/philo.h"

static long	r_atol(char *str)
{
	int		i;
	int		sig;
	long	res;

	res = 0;
	i = 0;
	sig = 1;
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

static int	max_number_check(int argc, char **argv)
{
	int	i;

	i = 1;
	while (++i < 5)
	{
		if (r_atol(argv[i]) > INT_MAX)
			return (-6);
	}
	if (argc == 6)
		if (r_atol(argv[5]) > INT_MAX)
			return (-6);
	return (0);
}

static void	r_perror(int error)
{
	printf("Usage: ./philo <number of philos> ");
	printf("<time to die(ms)> <time to eat(ms)> <time to sleep(ms)> ");
	printf("<(optional) number of times each philo eats>\n");
	if (error == -1)
		printf("Maximum of 200 philos!\n");
	if (error == -2)
		printf("Minimum of 0 meals each!\n");
	if (error == -3)
		printf("Invalid argument format!\n");
	if (error == -4)
		printf("Number of philos or time needs positive values!\n");
	if (error == -5)
		printf("Invalid number of arguments!\n");
	if (error == -6)
		printf("Values should not exceed the maximum integer\n");
}

static int	parsing(int argc, char **argv)
{
	int	i;

	i = argc - 1;
	if (argc > 6 || argc < 5)
		return (-5);
	if (r_atol(argv[1]) > 200)
		return (-1);
	if (argc == 6 && r_atol(argv[5]) < 0)
		return (-2);
	while (i > 0)
	{
		if (!r_isdigit(argv[i]))
			return (-3);
		i--;
	}
	i = 4;
	while (i > 0)
	{
		if (r_atol(argv[i]) <= 0)
			return (-4);
		i--;
	}
	if (max_number_check(argc, argv) != 0)
		return (-6);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	int		error;

	error = 0;
	error = parsing(argc, argv);
	if (error != 0)
	{
		r_perror(error);
		return (PARSING_ERROR);
	}
	if (ini_table(&table, argv, argc) != 0)
		return (ERROR_MALLOC);
	ini_philos(&table);
	ini_forks(&table);
	if (create_threads(&table) != 0)
		return (philo_free(&table), printf("Errors creating/joining threads!"));
	philo_free(&table);
}
