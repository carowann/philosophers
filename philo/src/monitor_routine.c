/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:47:33 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/30 12:58:38 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	someone_died(t_sim_data *sim_data)
{
	long	time_starving;
	int		i;

	i = 0;
	while (i < sim_data->n_philos)
	{
		pthread_mutex_lock(&sim_data->philos[i].meal_mutex);
		time_starving = get_timestamp(sim_data) - sim_data->philos[i].last_meal_time;
		pthread_mutex_unlock(&sim_data->philos[i].meal_mutex);
		if (time_starving > sim_data->time_to_die)
		{
			print_status(&sim_data->philos[i], "died");
			pthread_mutex_lock(&sim_data->sim_mutex);
			sim_data->simulation_running = 1;
			pthread_mutex_unlock(&sim_data->sim_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	all_have_eaten_enough(t_sim_data *sim_data)
{
	int	i;
	int	full_philos;

	i = 0;
	while (i < sim_data->n_philos)
	{
		//contare quanti sono pieni
	}
	// check if n philos == meals eaten
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim_data	*sim_data;
	int			i;
	long		time_starving;

	sim_data = (t_sim_data *)arg;
	while (!is_simulation_stopped(sim_data))
	{
		if (someone_died(sim_data))
			return (NULL);
		safe_usleep(sim_data, 1);
	}
	return (NULL);
}
