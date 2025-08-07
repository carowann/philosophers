/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/07 16:25:10 by cwannhed         ###   ########.fr       */
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

int	init_forks(t_data *data)
{
	int	i;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->n_philos)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != SUCCESS)
			return (0);
		i++;
	}
	return (1);
}

int	create_philos(t_data *data)
{
	int		i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (0);
	data->start_time = get_timestamp(data);
	data->stop = 0;
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].time_last_meal = data->start_time;
		data->philos[i].shared = data;
		data->philos[i].meals = 0;
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != SUCCESS)
		{
			//TODO: clean up prev threads
			return (0);
		}
		i++;
	}
	return (1);
}

int	wait_philos(t_data *shared)
{
	int	i;
		
	i = 0;
	while (i < shared->n_philos)
	{
		if (pthread_join(shared->philos[i].thread, NULL) != SUCCESS)
		{
			//TODO: clean up prev threadskj
			return (0);
		}
		i++;
	}
	return (1);
}

int destroy_forks(t_data *shared)
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
