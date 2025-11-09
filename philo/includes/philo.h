/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwannhed <cwannhed@student.42firenze.it>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 15:52:56 by cwannhed          #+#    #+#             */
/*   Updated: 2025/11/09 21:43:46 by cwannhed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* ========================================================================== */
/*                                 INCLUDES                                   */
/* ========================================================================== */

# include <pthread.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

/* ========================================================================== */
/*                                 DEFINES                                    */
/* ========================================================================== */

# define BOLD	"\033[1m"
# define BLUE	"\033[0;34m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define RESET	"\033[0m"
# define YELLOW	"\033[0;33m"
# define CYAN	"\033[0;36m"

enum e_code
{
	SUCCESS,
	FAILURE
};

enum e_philo_status
{
	EAT,
	SLEEP,
	FORK,
	THINK,
	DEATH
};

# define EAT_MSG	"is eating"
# define SLEEP_MSG	"is sleeping"
# define FORK_MSG	"has taken a fork"
# define THINK_MSG	"is thinking"
# define DEATH_MSG	"died"
# define VALID_ARGS_MSG	"Please input valid arguments\n"

# define MONITOR_SLEEP_MICROSECONDS	1000
# define PHILO_SLEEP_MICROSECONDS 500
# define USLEEP_CHECK_INTERVAL_MICROSECONDS 500
# define INFINITE_MEALS -1

/* ========================================================================== */
/*                              STRUCTURES                                    */
/* ========================================================================== */

typedef struct s_philo
{
	int					id;
	int					meals_eaten;
	long				last_meal_time;
	pthread_t			thread;
	pthread_mutex_t		meal_mutex;
	struct s_sim_data	*sim_data;
}				t_philo;

typedef struct s_sim_data
{
	int				n_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				required_meals;		// -1 if unlimited
	int				simulation_running;	// 0 = stop, 1 = running
	int				threads_created;
	long			start_time;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	sim_mutex;
	pthread_mutex_t	time_mutex;
	pthread_t		monitor_thread;
	t_philo			*philos;
}				t_sim_data;

/* ========================================================================== */
/*                         FUNCTION PROTOTYPES                               */
/* ========================================================================== */

/* === INITIALIZATION === */
void	init_simulation_data(t_sim_data *data);
void	init_forks(t_sim_data *data);

/* === INPUT VALIDATION === */
void	check_usage(int argc);
void	validate_args(int argc, char *argv[], t_sim_data *data);

/* === SIMULATION CONTROL === */
void	simulation(t_sim_data *data);
void	*routine(void *arg);
void	*monitor_routine(void *arg);
void	lonely_philo_simulation(t_sim_data *sim_data);
void	*lonely_philo_routine(void *arg);

/* === PHILOSOPHER ACTIONS === */
void	eat(t_philo *philo);
void	nap(t_philo *philo);

/* === THREAD SAFETY === */
int		is_simulation_stopped(t_sim_data *sim_data);
int		has_eaten_enough(t_philo *philo);

/* === CLEANUP === */
void	cleanup_and_exit(t_sim_data *data, int exit_code);
void	wait_philos(t_sim_data *data);
void	destroy_forks(t_sim_data *shared);
void	destroy_all_mutexes(t_sim_data *data);

/* === UTILITY FUNCTIONS === */
int		ft_isdigit(int c);
long	ft_atol(const char *nptr);
long	get_current_time_ms(t_sim_data *sim_data);
long	get_timestamp(t_sim_data *shared);
void	print_status(t_philo *philo, int status);
int		safe_usleep(t_sim_data *sim_data, int microseconds);

#endif