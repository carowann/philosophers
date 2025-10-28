/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/28 11:21:34 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_sim_data	simulation_data;
	pthread_t	monitor;

	check_usage(argc);
	validate_args(argc, argv, &simulation_data);
	init_simulation_data(&simulation_data);
	simulation(&simulation_data, &monitor);
	cleanup_and_exit(&simulation_data, &monitor, EXIT_SUCCESS);
}
