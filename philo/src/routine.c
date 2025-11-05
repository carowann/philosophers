/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:00:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/05 14:07:16 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		safe_usleep(philo->sim_data, 500);
	while (!is_simulation_stopped(philo->sim_data))
	{
		if (philo->sim_data->required_meals != -1 && has_eaten_enough(philo))
			break ;
		print_status(philo, THINK);
		eat(philo);
		nap(philo);
	}
	return (NULL);
}
static void	switch_forks(int *first, int *second)
{
	int	temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

void	takes_forks(t_philo *philo)
{
	int	temp;

	temp = 0;
	philo->first_fork = (philo->id - 1) % philo->sim_data->n_philos;
	philo->second_fork = philo->id % philo->sim_data->n_philos;
	if (philo->first_fork > philo->second_fork)
		switch_forks(&philo->first_fork, &philo->second_fork);
	// if (philo->id == philo->sim_data->n_philos && philo->sim_data->n_philos % 2 == 1)
	// 	switch_forks(&philo->first_fork, &philo->second_fork);
	if (philo->sim_data->n_philos % 2 == 1)
		pthread_mutex_lock(&philo->sim_data->waiter_mutex);
	pthread_mutex_lock(&philo->sim_data->fork_mutex[philo->first_fork]);
	print_status(philo, FORK);
	if (is_simulation_stopped(philo->sim_data))
	{
		pthread_mutex_unlock(&philo->sim_data->fork_mutex[philo->first_fork]);
		if (philo->sim_data->n_philos % 2 == 1)
			pthread_mutex_unlock(&philo->sim_data->waiter_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->sim_data->fork_mutex[philo->second_fork]);
	print_status(philo, FORK);
	if (philo->sim_data->n_philos % 2 == 1)
		pthread_mutex_unlock(&philo->sim_data->waiter_mutex);
}

void	eat(t_philo *philo)
{
	takes_forks(philo);
	if (is_simulation_stopped(philo->sim_data))
	{
		pthread_mutex_unlock(&philo->sim_data->fork_mutex[philo->second_fork]);
		pthread_mutex_unlock(&philo->sim_data->fork_mutex[philo->first_fork]);
		return;
	}
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = get_timestamp(philo->sim_data);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, EAT);
	safe_usleep(philo->sim_data, philo->sim_data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->sim_data->fork_mutex[philo->second_fork]);
	pthread_mutex_unlock(&philo->sim_data->fork_mutex[philo->first_fork]);
}

void	nap(t_philo *philo)
{
	print_status(philo, SLEEP);
	safe_usleep(philo->sim_data, philo->sim_data->time_to_sleep * 1000);
}
