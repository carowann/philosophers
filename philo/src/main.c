/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/06 10:09:37 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

//ideas for solution
//data struct w/ priority, whoever ate too long ago, jumps the queue
//mutual exclusion: no process can access shared data and cause data races

int	main(int argc, char *argv[])
{
	// pthread_mutex_t	mutex;
	t_data			shared;

	shared = (t_data){0};
	if (!valid_args(argc, argv, &shared))
		return (1);
	if (!init_forks(&shared))
		return (1);
	if (!create_philos(&shared))
		return (1);
	if (!wait_philos(&shared))
		return (1);
	if (!destroy_forks(&shared))
		return (1);
	return (0);
}