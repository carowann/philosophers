/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/15 11:53:27 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data		shared;
	pthread_t	monitor;

	shared = (t_data){0};
	if (!valid_args(argc, argv, &shared))
		return (1);
	if (!init_forks(&shared))
		return (1);
	if (!create_philos(&shared))
		return (1);
	if (pthread_create(&monitor, NULL, monitor_routine, &shared) != SUCCESS)
		return (1);
	if (!wait_philos(&shared))
		return (1);
	if (pthread_join(monitor, NULL) != SUCCESS)
		return (1);
	if (!destroy_forks(&shared))
		return (1);
	free(shared.forks);
	free(shared.philos);
	return (0);
}
