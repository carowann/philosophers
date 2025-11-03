/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 12:47:33 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/03 11:44:54 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	someone_died(t_sim_data *sim_data)
{
	long	time_starving;
	long	current_time;
	int		i;

	i = 0;
	while (i < sim_data->n_philos)
	{
		current_time = get_timestamp(sim_data);
		pthread_mutex_lock(&sim_data->philos[i].meal_mutex);
		time_starving = current_time - sim_data->philos[i].last_meal_time;
		pthread_mutex_unlock(&sim_data->philos[i].meal_mutex);
		if (time_starving > sim_data->time_to_die)
		{
			print_status(&sim_data->philos[i], DEATH);
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
	int	meals;

	i = 0;
	full_philos = 0;
	if (sim_data->required_meals == -1)
		return (0);
	while (i < sim_data->n_philos)
	{
		pthread_mutex_lock(&sim_data->philos[i].meal_mutex);
		meals = sim_data->philos[i].meals_eaten;
		pthread_mutex_unlock(&sim_data->philos[i].meal_mutex);
		if (meals >= sim_data->required_meals)
			full_philos++;
		i++;
	}
	if (full_philos == sim_data->n_philos)
	{
		pthread_mutex_lock(&sim_data->sim_mutex);
		sim_data->simulation_running = 1;
		pthread_mutex_unlock(&sim_data->sim_mutex);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_sim_data	*sim_data;

	sim_data = (t_sim_data *)arg;
	while (!is_simulation_stopped(sim_data))
	{
		if (someone_died(sim_data))
			return (NULL);
		if (all_have_eaten_enough(sim_data))
			return (NULL);
		safe_usleep(sim_data, 1);
	}
	return (NULL);
}
