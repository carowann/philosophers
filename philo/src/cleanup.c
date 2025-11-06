/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:31:26 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/31 15:28:48 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_and_exit(t_sim_data *sim_data, int exit_code)
{
	if (sim_data)
	{
		wait_philos(sim_data);
		if (sim_data->monitor_thread)
			pthread_join(sim_data->monitor_thread, NULL);
		destroy_all_mutexes(sim_data);
		free(sim_data->fork_mutex);
		free(sim_data->philos);
	}
	exit(exit_code);
}

void	destroy_forks(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->fork_mutex[i]);
		i++;
	}
}

void	destroy_all_mutexes(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	destroy_forks(sim_data);
	pthread_mutex_destroy(&sim_data->print_mutex);
	pthread_mutex_destroy(&sim_data->time_mutex);
	while (i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->philos[i].meal_mutex);
		i++;
	}
}

void	wait_philos(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->threads_created)
	{
		pthread_join(sim_data->philos[i].thread, NULL);
		i++;
	}
}
