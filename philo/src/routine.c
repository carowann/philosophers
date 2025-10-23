/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:00:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/23 11:11:03 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo->shared->stop) //death or enough meals if specified
	{
		if (philo->shared->n_times_philos_eat != -1 && philo->meals >= philo->shared->n_times_philos_eat)
			break;
		print_status(philo, "is thinking");
		if (!philo->shared->stop)
			eat(philo);
		if (!philo->shared->stop)
			nap(philo);
	}
	return (NULL);
}

void eat(t_philo *philo)
{
	int		left;
	int		right;
	long	timestamp;

	if (philo->shared->n_philos == 1)
	{

		return ;
	}
	left = philo->id - 1;
	right = philo->id % philo->shared->n_philos;
	if (philo->shared->stop)
		return ;
	if (philo->id == philo->shared->n_philos)
	{
		pthread_mutex_lock(&philo->shared->forks[right]);
		if (!philo->shared->stop)
			print_status(philo, "has taken a fork");
		if (philo->shared->stop)
		{
			pthread_mutex_unlock(&philo->shared->forks[right]);
			return ;
		}
		pthread_mutex_lock(&philo->shared->forks[left]);
		if (!philo->shared->stop)
			print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->shared->forks[left]);
		if (!philo->shared->stop)
			print_status(philo, "has taken a fork");
		if (philo->shared->stop)
		{
			pthread_mutex_unlock(&philo->shared->forks[left]);
			return ;
		}
		pthread_mutex_lock(&philo->shared->forks[right]);
		if (!philo->shared->stop)
			print_status(philo, "has taken a fork");
	}
	if (philo->shared->stop)
	{
		pthread_mutex_unlock(&philo->shared->forks[left]);
		pthread_mutex_unlock(&philo->shared->forks[right]);
		return;
	}
	timestamp = get_timestamp(philo->shared);
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->meal_mutex);
	philo->time_last_meal = timestamp;
	philo->meals++;
	pthread_mutex_unlock(&philo->meal_mutex);
	usleep(philo->shared->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->shared->forks[left]);
	pthread_mutex_unlock(&philo->shared->forks[right]);
}


void	nap(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_timestamp(philo->shared), philo->id);
	usleep(philo->shared->time_to_sleep * 1000);
}
