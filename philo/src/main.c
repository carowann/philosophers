/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:05 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/04 18:18:06 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*routine()
{

}

int	main(int argc, char *argv[])
{
	pthread_t		t1;
	pthread_mutex_t	mutex;
	t_data			*data;

	if (validate_args(argc, *argv, data) == FAILURE)
		return (1);
	pthread_mutex_init(&mutex, NULL);
	create_philos(*data)
	if (pthread_create(&t1, NULL, &routine, NULL) != SUCCESS) //The  pthread_create()  function  starts  a  new  thread  in the calling process.
		return (1);
	if (pthread_join(t1, NULL) != SUCCESS) //The pthread_join() function waits for the thread specified by thread to terminate.
		return (1);
	pthread_mutex_destroy(&mutex);
	return (0);
}