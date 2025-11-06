/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:39:53 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/31 15:07:53 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	check_usage(int argc)
{
	if (argc != 5 && argc != 6)
	{
		write(2, BOLD"Usage: ./philo"RESET, 25);
		write(2, BLUE" number_of_philosophers "RESET, 35);
		write(2, RED"time_to_die "RESET, 22);
		write(2, CYAN"time_to_eat "RESET, 23);
		write(2, GREEN"time_to_sleep "RESET, 26);
		write(2, "[number_of_times_each_philosopher_must_eat]\n", 45);
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
	long			current_time;
	long			result;

	pthread_mutex_lock(&sim_data->time_mutex);
	if (gettimeofday(&tv, NULL) != SUCCESS)
	{
		pthread_mutex_unlock(&sim_data->time_mutex);
		cleanup_and_exit(sim_data, EXIT_FAILURE);
	}
	current_time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	result = current_time - sim_data->start_time;
	if (result < 0)
		result = 0;
	pthread_mutex_unlock(&sim_data->time_mutex);
	return (result);
}

long	get_current_time_ms(t_sim_data	*sim_data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != SUCCESS)
		cleanup_and_exit(sim_data, EXIT_FAILURE);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}
