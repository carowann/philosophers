/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:31:26 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/23 12:00:43 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_and_exit(t_data *data, pthread_t *monitor, int exit_code)
{
	wait_philos(data);
	pthread_join(*monitor, NULL);
	destroy_all_mutexes(data);
	free(data->forks);
	free(data->philos);
	exit(exit_code);
}

void	destroy_forks(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
	{
		pthread_mutex_destroy(&shared->forks[i]);
		i++;
	}
}

void	destroy_all_mutexes(t_data *data)
{
	destroy_forks(data);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->philos->meal_mutex);
}