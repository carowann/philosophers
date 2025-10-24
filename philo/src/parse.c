/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:14 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/24 11:07:41 by cwannhed         ###   ########.fr       */
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

void	validate_args(int argc, char *argv[], t_sim_data *sim_data)
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
	sim_data->n_philos = (int)values[0];
	sim_data->time_to_die = (int)values[1];
	sim_data->time_to_eat = (int)values[2];
	sim_data->time_to_sleep = (int)values[3];
	if (argc == 6)
		sim_data->required_meals = (int)values[4];
	else
		sim_data->required_meals = -1;
	return ;
}
