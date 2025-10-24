/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:39:53 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/24 11:08:53 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_usage(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, "Usage: ./philo number_of_philosophers time_to_die", 50);
		write(2, " time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", 72);
		exit(EXIT_FAILURE);
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	long	nbr;
	int		sign;

	nbr = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr = nbr * 10 + (*nptr - '0');
		nptr++;
	}
	return (sign * nbr);
}

long	get_timestamp(t_sim_data *sim_data)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	//TODO:protect
	timestamp = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - sim_data->start_time);
	return (timestamp);
}

// Funzione helper per i print thread-safe
void print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->sim_data->print_mutex);
	if (!philo->sim_data->simulation_running)
		printf("%ld %d %s\n", get_timestamp(philo->sim_data), philo->id, status);
	pthread_mutex_unlock(&philo->sim_data->print_mutex);
}
