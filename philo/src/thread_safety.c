/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_safety.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:32:36 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/04 14:23:05 by cwannhed         ###   ########.fr       */
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

void	print_status(t_philo *philo, int status)
{
	long	timestamp;

	timestamp = get_timestamp(philo->sim_data);
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	if (!is_simulation_stopped(philo->sim_data))
	{
		if (status == DEATH)
			printf(RED"%ld %d %s\n"RESET, timestamp, philo->id, DEATH_MSG);
		else if (status == EAT)
			printf(CYAN"%ld %d %s\n"RESET, timestamp, philo->id, EAT_MSG);
		else if (status == FORK)
			printf(YELLOW"%ld %d %s\n"RESET, timestamp, philo->id, FORK_MSG);
		else if (status == SLEEP)
			printf(GREEN"%ld %d %s\n"RESET, timestamp, philo->id, SLEEP_MSG);
		else
			printf("%ld %d %s\n", timestamp, philo->id, THINK_MSG);
	}
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
}

int	safe_usleep(t_sim_data *sim_data, int microseconds)
{
	long	start_time;
	long	current_time;
	long	elapsed;

	start_time = get_current_time_ms(sim_data) * 1000;
	while (1)
	{
		if (is_simulation_stopped(sim_data))
			return (1);
		current_time = get_current_time_ms(sim_data) * 1000;
		elapsed = current_time - start_time;
		if (elapsed >= microseconds)
			return (0);
		if (usleep(500) != SUCCESS)
			cleanup_and_exit(sim_data, EXIT_FAILURE);
	}
}
