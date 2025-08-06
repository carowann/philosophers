/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:56 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/06 10:04:31 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>

enum code
{
	SUCCESS,
	FAILURE
};

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
}				t_philo;

typedef struct s_shared
{
	int				n_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_philos_eat;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}				t_data;



//parse.c
int	valid_args(int argc, char *argv[], t_data *data);
int	valid_format(char *arg);

//utils.c
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);

//thread_mgmt.c
void	*routine(void *arg);
int		create_philos(t_data *data);
int		wait_philos(t_data *data);

#endif
