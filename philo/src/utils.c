/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 12:39:53 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/07 16:15:35 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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

long	get_timestamp(t_data *shared)
{
	struct timeval	tv;
	long			timestamp;
	
	gettimeofday(&tv, NULL);
	//TODO:protect
	timestamp = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - shared->start_time);
	return (timestamp);
}