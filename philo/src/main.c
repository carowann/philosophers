/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/31 15:05:35 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_sim_data	simulation_data;

	check_usage(argc);
	validate_args(argc, argv, &simulation_data);
	init_simulation_data(&simulation_data);
	simulation(&simulation_data);
	cleanup_and_exit(&simulation_data, EXIT_SUCCESS);
}
