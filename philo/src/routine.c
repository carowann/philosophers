/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 12:00:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/07 16:24:50 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	eat(t_philo	*philo)
{
	int		left;
	int		right;
	long	timestamp;

	left = philo->id - 1;
	right = philo->id % philo->shared->n_philos;
	if (philo->shared->stop)
		return;
	pthread_mutex_lock(&philo->shared->forks[left]);
	//TODO: protect
	printf("%ld %d has taken a fork\n", get_timestamp(philo->shared), philo->id);
	if (philo->shared->stop)
	{
		pthread_mutex_unlock(&philo->shared->forks[left]);
		return;
	}
	pthread_mutex_lock(&philo->shared->forks[right]);
	printf("%ld %d has taken a fork\n", get_timestamp(philo->shared), philo->id);
	timestamp = get_timestamp(philo->shared);
	printf("%ld %d is eating\n", timestamp, philo->id);
	philo->time_last_meal = timestamp;
	philo->meals++;
	usleep(philo->shared->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->shared->forks[left]);
	pthread_mutex_unlock(&philo->shared->forks[right]);
}

void	nap(t_philo *philo)
{
	printf("%ld %d is sleeping\n", get_timestamp(philo->shared), philo->id);
	usleep(philo->shared->time_to_sleep * 1000);
}
