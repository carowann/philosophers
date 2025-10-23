/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/23 12:00:33 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	pthread_t	monitor;

	check_usage(argc);
	validate_args(argc, argv, &data);
	init_data(&data);
	simulation(&data, &monitor);
	cleanup_and_exit(&data, &monitor, EXIT_SUCCESS);
}
