/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/06 10:13:14 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	printf("philo id %d \n", philo->id);
	return (NULL);
}

int	init_forks(t_data *data)
{
	int	i;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philos);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->forks)
	{
		if(pthread_mutex_init(&data->forks[i], NULL) != SUCCESS)
			return (0);
		i++;
	}
	return (1);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->n_philos);
	if (!data->philos)
		return (0);
	i = 0;
	while (i < data->n_philos)
	{
		data->philos[i].id = i + 1;
		// init other data
		if (pthread_create(&data->philos[i].thread, NULL, routine, &data->philos[i]) != SUCCESS)
		{
			//TODO: clean up prev threads
			return (1);
		}
		printf("thread %d has started\n", i);
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
		shared->philos[i].id = i + 1;
		// init other shared data
		if (pthread_join(shared->philos[i].thread, NULL) != SUCCESS)
		{
			//TODO: clean up prev threads
			return (0);
		}
		printf("thread %d has finished execution\n", i);
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
