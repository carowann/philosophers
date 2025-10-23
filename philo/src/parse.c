/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:14 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/23 11:11:43 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	validate_format(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i = 1;
	if (!arg[i])
		exit(EXIT_FAILURE);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			exit(EXIT_FAILURE);
		i++;
	}
	return ;
}

void	validate_args(int argc, char *argv[], t_data *data)
{
	long	values[5];
	int		i;

	i = 1;

	while (i < argc)
	{
		validate_format(argv[i]);
		values[i - 1] = ft_atol(argv[i]);
		if (values[i - 1] <= 0 || values[i - 1] > INT_MAX)
			exit(EXIT_FAILURE);
		i++;
	}
	data->n_philos = (int)values[0];
	data->time_to_die = (int)values[1];
	data->time_to_eat = (int)values[2];
	data->time_to_sleep = (int)values[3];
	if (argc == 6)
		data->n_times_philos_eat = (int)values[4];
	else
		data->n_times_philos_eat = -1;
	return ;
}
