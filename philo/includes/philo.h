/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:56 by cwannhed          #+#    #+#             */
/*   Updated: 2025/10/23 12:00:56 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

enum code
{
	SUCCESS,
	FAILURE
};

typedef struct s_philo
{
	int				id;
	int				meals;
	pthread_t		thread;
	pthread_mutex_t	meal_mutex;
	long			time_last_meal;
	struct s_data	*shared;
}				t_philo;

typedef struct s_data
{
	int				n_philos;
	int				threads_created;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_philos_eat;
	int				stop;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	t_philo			*philos;
}				t_data;

void	init_data(t_data *data);
void	check_usage(int argc);
void	cleanup_and_exit(t_data *data, pthread_t *monitor,int exit_code);
void	validate_args(int argc, char *argv[], t_data *data);
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	get_timestamp(t_data *shared);
void	print_status(t_philo *philo, char *status);
void	*routine(void *arg);
void	init_forks(t_data *data);
void	simulation(t_data *data, pthread_t *monitor);
void	wait_philos(t_data *data);
void	destroy_forks(t_data *shared);
void	*monitor_routine(void*arg);
void	eat(t_philo	*philo);
void	nap(t_philo *philo);
void	destroy_all_mutexes(t_data *data);

#endif
