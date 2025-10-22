/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/22 14:40:50 by cwannhed         ###   ########.fr       */
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
		//TODO: mutex printf
		printf("%ld %d is thinking\n", get_timestamp(philo->shared), philo->id);
		if (!philo->shared->stop)
			eat(philo);
		if (!philo->shared->stop)
			nap(philo);
	}
	return (NULL);
}

// int init_mutexes(t_data *data)
// {
// 	if (pthread_mutex_init(&data->print_mutex, NULL) != SUCCESS)
// 		return (0);
// 	if (pthread_mutex_init(&data->philos->meal_mutex, NULL) != SUCCESS)
// 		return (0);
// 	if (init_forks(data) != SUCCESS)
// 		return (0);
// 	return (1);
// }

void	init_forks(t_data *data)
{
	int	i;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != SUCCESS)
			cleanup_and_exit(data, EXIT_FAILURE);
		i++;
	}
	return ;
}

void	init_philo(t_philo **philo, int i, t_data *data)
{
	(*philo)->id = i + 1;
	(*philo)->time_last_meal = data->start_time;
	(*philo)->shared = data;
	(*philo)->meals = 0;
	return ;
}

void	init_data(t_data **data)
{
	(*data)->philos = malloc(sizeof(t_philo) * (*data)->n_philos);
	if (!(*data)->philos)
		exit(EXIT_FAILURE);
	(*data)->start_time = get_timestamp((*data));
	(*data)->stop = 0;
	(*data)->threads_created = 0;
}

void	lonely_philo(t_data *data, t_philo *philo)
{
	init_philo(&philo, 0, data);
	pthread_mutex_lock(&philo->shared->forks[0]);
	print_status(philo, "has taken a fork");
	usleep(philo->shared->time_to_die * 1000);
	pthread_mutex_unlock(&philo->shared->forks[0]);
	print_status(philo, "has died");
	cleanup_and_exit(data, EXIT_SUCCESS);
}

void	create_philos_and_monitor(t_data *data, pthread_t *monitor)
{
	int	i;

	init_data(&data);
	i = 0;
	if (data->n_philos == 1)
		lonely_philo(data, &data->philos[0]);
	while (i < data->n_philos)
	{
		init_philo(&data->philos[i], i, data);
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != 0)
			cleanup_and_exit(data, EXIT_FAILURE);
		data->threads_created++;
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, data) != 0)
	{
		wait_philos(data);
		cleanup_and_exit(data, EXIT_FAILURE);
	}
}

int	wait_philos(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->threads_created)
	{
		pthread_join(shared->philos[i].thread, NULL);
		i++;
	}
	return (1);
}

int	destroy_mutexes(t_data *shared)
{
	if (pthread_mutex_destroy(&shared->print_mutex))
		return (0);
	if (pthread_mutex_destroy(&shared->philos->meal_mutex))
		return (0);
	if (destroy_forks(shared) != SUCCESS)
		return (0);
	return (1);
}

int	destroy_forks(t_data *shared)
{
	int	i;

	i = 0;
	while (i < shared->n_philos)
	{
		if (pthread_mutex_destroy(&shared->forks[i]))
			return(0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_data	*shared;
	int		i;
	long	time_starving;

	shared = (t_data *)arg;
	while (!shared->stop)
	{
		i = 0;
		while (i < shared->n_philos)
		{
			time_starving = get_timestamp(shared) - shared->philos[i].time_last_meal;
			if (time_starving >= shared->time_to_die)
			{
				printf("%ld %d died\n", get_timestamp(shared), shared->philos[i].id);
				shared->stop = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
