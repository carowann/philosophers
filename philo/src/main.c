/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/17 16:26:39 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data		shared;
	pthread_t	monitor;

	memset(&shared, 0, sizeof(t_data));
	validate_args(argc, argv, &shared);
	init_forks(&shared);
	create_philos_and_monitor(&shared, &monitor);
	wait_philos(&shared);
	pthread_join(monitor, NULL);
	cleanup_and_exit(&shared, EXIT_SUCCESS);
}
