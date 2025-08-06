/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:56 by cwannhed          #+#    #+#             */
/*   Updated: 2025/08/06 11:51:44 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

enum code
{
	SUCCESS,
	FAILURE
};

typedef struct s_philo
{
	int			id;
	pthread_t	thread;
	long		time_last_meal;
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
long	get_curr_time_ms(void);

//thread_mgmt.c
void	*routine(void *arg);
int		init_forks(t_data *data);
int		create_philos(t_data *data);
int		wait_philos(t_data *data);
int		destroy_forks(t_data *shared);

#endif
