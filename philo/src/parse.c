/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:13:14 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/04 17:40:54 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	validate_args(int argc, char ***argv, t_data *data)
{
	if (argc != 5 && argc != 6)
		return (FAILURE);
	//TODO: check if args are valid numbers
	data->n_philos = argv[1];
	data->time_to_die = argv[2];
	data->time_to_eat = argv[3];
	data->time_to_sleep = argv[4];
	if (argc == 6)
		data->n_times_philos_eat = argv[5];
	else
		data->n_times_philos_eat = -1;
	return (SUCCESS);
}
