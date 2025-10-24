/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/24 11:15:40 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

void	init_forks(t_sim_data *sim_data)
{
	int	i;
	sim_data->forks = malloc(sizeof(pthread_mutex_t) * sim_data->n_philos);
	if (!sim_data->forks)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < sim_data->n_philos)
	{
		if (pthread_mutex_init(&sim_data->forks[i], NULL) != SUCCESS)
			cleanup_and_exit(sim_data, NULL, EXIT_FAILURE);
		i++;
	}
}

void	init_philo(t_philo *philo, int i, t_sim_data *sim_data)
{
	philo->id = i + 1;
	philo->last_meal_time = sim_data->start_time;
	philo->sim_data = sim_data;
	philo->meals_eaten = 0;
	if (pthread_mutex_init(&philo->meal_mutex, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, NULL, EXIT_FAILURE);
}

void	init_simulation_data(t_sim_data *sim_data)
{
	init_forks(sim_data);
	sim_data->philos = malloc(sizeof(t_philo) * sim_data->n_philos);
	if (!sim_data->philos)
		exit(EXIT_FAILURE);
	//TODO: init all mutexes
	if (pthread_mutex_init(&sim_data->print_mutex, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, NULL, EXIT_FAILURE);
	sim_data->start_time = get_timestamp(sim_data);
	sim_data->simulation_running = 0;
	sim_data->threads_created = 0;
}

void	lonely_philo_simulation(t_sim_data *sim_data, t_philo *philo)
{
	init_philo(philo, 0, sim_data);
	pthread_mutex_lock(&philo->sim_data->forks[0]);
	print_status(philo, "has taken a fork");
	usleep(philo->sim_data->time_to_die * 1000);
	pthread_mutex_unlock(&philo->sim_data->forks[0]);
	print_status(philo, "has died");
	cleanup_and_exit(sim_data, NULL, EXIT_SUCCESS);
}

void	simulation(t_sim_data *sim_data, pthread_t *monitor)
{
	int	i;

	i = 0;
	if (sim_data->n_philos == 1)
		lonely_philo_simulation(sim_data, &sim_data->philos[0]);
	while (i < sim_data->n_philos)
	{
		init_philo(&sim_data->philos[i], i, sim_data);
		if (pthread_create(&sim_data->philos[i].thread, NULL, routine, &sim_data->philos[i]) != 0)
			cleanup_and_exit(sim_data, NULL, EXIT_FAILURE);
		sim_data->threads_created++;
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_routine, sim_data) != SUCCESS)
		cleanup_and_exit(sim_data, NULL, EXIT_FAILURE);
}

void	wait_philos(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	while (i < sim_data->threads_created)
	{
		pthread_join(sim_data->philos[i].thread, NULL);
		i++;
	}
}

// int	destroy_mutexes(t_sim_data *sim_data)
// {
// 	if (pthread_mutex_destroy(&sim_data->print_mutex))
// 		return (0);
// 	if (pthread_mutex_destroy(&sim_data->philos->meal_mutex))
// 		return (0);
// 	if (destroy_forks(sim_data) != SUCCESS)
// 		return (0);
// 	return (1);
// }

void	*monitor_routine(void *arg)
{
	t_sim_data	*sim_data;
	int		i;
	long	time_starving;

	sim_data = (t_sim_data *)arg;
	while (!sim_data->simulation_running)
	{
		i = 0;
		while (i < sim_data->n_philos)
		{
			time_starving = get_timestamp(sim_data) - sim_data->philos[i].last_meal_time;
			if (time_starving >= sim_data->time_to_die)
			{
				print_status(&sim_data->philos[i], "died");
				sim_data->simulation_running = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
