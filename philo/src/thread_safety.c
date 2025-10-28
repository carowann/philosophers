/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safety.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:32:36 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/28 13:03:57 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	is_simulation_stopped(t_sim_data *sim_data)
{
	int	result;

	pthread_mutex_lock(&sim_data->sim_mutex);
	result = sim_data->simulation_running;
	pthread_mutex_unlock(&sim_data->sim_mutex);
	return (result);
}

int	has_eaten_enough(t_philo *philo)
{
	int	result;

	result = 0;
	if (philo->sim_data->required_meals == -1)
		return (result);
	pthread_mutex_lock(&philo->meal_mutex);
	result = (philo->meals_eaten >= philo->sim_data->required_meals);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (result);
}
