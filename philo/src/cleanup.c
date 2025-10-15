/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:31:26 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/15 12:36:13 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	cleanup_and_exit(t_data *data, int exit_code)
{
	wait_philos(data);
	destroy_forks(data);
	free(data->forks);
	free(data->philos);
	exit(exit_code);
}
