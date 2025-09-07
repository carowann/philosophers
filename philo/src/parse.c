/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:14 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/12 13:18:41 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	valid_format(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i = 1;
	if (!arg[i])
		return (0);
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return(0);
		i++;
	}
	return (1);
}

int	valid_args(int argc, char *argv[], t_data *data)
{
	long	values[5];
	int		i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	while (i < argc)
	{
		if (!valid_format(argv[i]))
			return (0);
		values[i - 1] = ft_atol(argv[i]);
		if (values[i - 1] <= 0 || values[i - 1] > INT_MAX)
			return (0);
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
	return (1);
}
