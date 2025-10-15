/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/15 12:02:56 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data shared;
	pthread_t monitor;

	memset(&shared, 0, sizeof(t_data));
	if (!valid_args(argc, argv, &shared))
		return (1);
	if (!init_forks(&shared))
		return (1);
	if (!create_philos(&shared))
	{
		destroy_forks(&shared);
		free(shared.forks);
		free(shared.philos);
		return (1);
	}
	if (pthread_create(&monitor, NULL, monitor_routine, &shared) != 0)
	{
		shared.stop = 1;
		wait_philos(&shared);
		destroy_forks(&shared);
		free(shared.forks);
		free(shared.philos);
		return (1);
	}
	wait_philos(&shared);
	pthread_join(monitor, NULL);
	destroy_forks(&shared);
	free(shared.forks);
	free(shared.philos);
	return (0);
}
