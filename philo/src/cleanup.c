/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:31:26 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/24 11:14:47 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_and_exit(t_sim_data *sim_data, pthread_t *monitor, int exit_code)
{
	wait_philos(sim_data);
	pthread_join(*monitor, NULL);
	destroy_all_mutexes(sim_data);
	free(sim_data->forks);
	free(sim_data->philos);
	exit(exit_code);
}

void	destroy_forks(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->forks[i]);
		i++;
	}
}

void	destroy_all_mutexes(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	destroy_forks(sim_data);
	pthread_mutex_destroy(&sim_data->print_mutex);
	while (i < sim_data->n_philos)
	{
		pthread_mutex_destroy(&sim_data->philos[i].meal_mutex);
		i++;
	}
}