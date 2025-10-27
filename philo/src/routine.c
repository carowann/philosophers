/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:00:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/24 11:37:57 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->sim_data->simulation_running) //death or enough meals_eaten if specified
	{
		if (philo->sim_data->required_meals != -1 && philo->meals_eaten >= philo->sim_data->required_meals)
			break;
		print_status(philo, "is thinking");
		if (!philo->sim_data->simulation_running)
			eat(philo);
		if (!philo->sim_data->simulation_running)
			nap(philo);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	int		left;
	int		right;
	long	timestamp;

	if (philo->sim_data->n_philos == 1)
	{

		return ;
	}
	left = philo->id - 1;
	right = philo->id % philo->sim_data->n_philos;
	if (philo->sim_data->simulation_running)
		return ;
	if (philo->id == philo->sim_data->n_philos)
	{
		pthread_mutex_lock(&philo->sim_data->forks[right]);
		if (!philo->sim_data->simulation_running)
			print_status(philo, "has taken a fork");
		if (philo->sim_data->simulation_running)
		{
			pthread_mutex_unlock(&philo->sim_data->forks[right]);
			return ;
		}
		pthread_mutex_lock(&philo->sim_data->forks[left]);
		if (!philo->sim_data->simulation_running)
			print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->sim_data->forks[left]);
		if (!philo->sim_data->simulation_running)
			print_status(philo, "has taken a fork");
		if (philo->sim_data->simulation_running)
		{
			pthread_mutex_unlock(&philo->sim_data->forks[left]);
			return ;
		}
		pthread_mutex_lock(&philo->sim_data->forks[right]);
		if (!philo->sim_data->simulation_running)
			print_status(philo, "has taken a fork");
	}
	if (philo->sim_data->simulation_running)
	{
		pthread_mutex_unlock(&philo->sim_data->forks[left]);
		pthread_mutex_unlock(&philo->sim_data->forks[right]);
		return;
	}
	timestamp = get_timestamp(philo->sim_data);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = timestamp;
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->sim_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->sim_data->forks[left]);
	pthread_mutex_unlock(&philo->sim_data->forks[right]);
}


void	nap(t_philo *philo)
{
	print_status(philo, "is sleeping");
	usleep(philo->sim_data->time_to_sleep * 1000);
}
