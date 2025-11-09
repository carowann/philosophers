/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:01:28 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/09 21:44:05 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_forks(t_sim_data *sim_data)
{
	int	i;

	sim_data->fork_mutex = malloc(sizeof(pthread_mutex_t) * sim_data->n_philos);
	if (!sim_data->fork_mutex)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < sim_data->n_philos)
	{
		if (pthread_mutex_init(&sim_data->fork_mutex[i], NULL) != SUCCESS)
			cleanup_and_exit(sim_data, EXIT_FAILURE);
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
		cleanup_and_exit(sim_data, EXIT_FAILURE);
}

void	init_simulation_data(t_sim_data *sim_data)
{
	init_forks(sim_data);
	sim_data->philos = malloc(sizeof(t_philo) * sim_data->n_philos);
	if (!sim_data->philos)
		exit(EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->print_mutex, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->sim_mutex, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, EXIT_FAILURE);
	if (pthread_mutex_init(&sim_data->time_mutex, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, EXIT_FAILURE);
	sim_data->start_time = get_current_time_ms(sim_data);
	sim_data->simulation_running = 0;
	sim_data->threads_created = 0;
	sim_data->monitor_thread = 0;
}

void	lonely_philo_simulation(t_sim_data *sim_data)
{
		init_philo(&sim_data->philos[0], 0, sim_data);
		if (pthread_create(&sim_data->philos[0].thread,
				NULL,
				lonely_philo_routine,
				&sim_data->philos[0]) != 0)
			cleanup_and_exit(sim_data, EXIT_FAILURE);
		sim_data->threads_created++;
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

void	simulation(t_sim_data *sim_data)
{
	int	i;

	i = 0;
	if (sim_data->n_philos == 1)
	{
		lonely_philo_simulation(sim_data);
		return ;
	}
	while (i < sim_data->n_philos)
	{
		init_philo(&sim_data->philos[i], i, sim_data);
		if (pthread_create(&sim_data->philos[i].thread,
				NULL,
				routine,
				&sim_data->philos[i]) != 0)
			cleanup_and_exit(sim_data, EXIT_FAILURE);
		sim_data->threads_created++;
		i++;
	}
	if (pthread_create(&sim_data->monitor_thread,
			NULL,
			monitor_routine,
			sim_data) != SUCCESS)
		cleanup_and_exit(sim_data, EXIT_FAILURE);
}
