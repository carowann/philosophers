/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:00:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/10 10:15:42 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		safe_usleep(philo->sim_data, PHILO_SLEEP_MICROSECONDS);
	while (!is_simulation_stopped(philo->sim_data))
	{
		if (philo->sim_data->required_meals != INFINITE_MEALS
			&& has_eaten_enough(philo))
			break ;
		print_status(philo, THINK);
		eat(philo);
		nap(philo);
	}
	return (NULL);
}

void	takes_forks(t_philo *philo, int left, int right)
{
	pthread_mutex_lock(&philo->sim_data->fork_mutex[right]);
	print_status(philo, FORK);
	pthread_mutex_lock(&philo->sim_data->fork_mutex[left]);
	print_status(philo, FORK);
}

void	eat(t_philo *philo)
{
	int		left;
	int		right;
	long	timestamp;

	left = philo->id - 1;
	right = philo->id % philo->sim_data->n_philos;
	if (philo->id % 2 != 0)
		takes_forks(philo, left, right);
	else
		takes_forks(philo, right, left);
	timestamp = get_timestamp(philo->sim_data);
	print_status(philo, EAT);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = timestamp;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	safe_usleep(philo->sim_data, philo->sim_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->sim_data->fork_mutex[left]);
	pthread_mutex_unlock(&philo->sim_data->fork_mutex[right]);
}

void	nap(t_philo *philo)
{
	print_status(philo, SLEEP);
	safe_usleep(philo->sim_data, philo->sim_data->time_to_sleep * 1000);
}

void	*lonely_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	print_status(philo, THINK);
	print_status(philo, FORK);
	safe_usleep(philo->sim_data, (philo->sim_data->time_to_die + 1) * 1000);
	print_status(philo, DEATH);
	return (NULL);
}
