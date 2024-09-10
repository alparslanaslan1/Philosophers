/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:57:15 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/11 00:59:24 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
#include <stdint.h>


# define M_ERROR "ERROR! AlLocation error.\n"
# define CHECK_ARGS "Check ur ARGS.\n"
# define MUTEX_INIT_ERROR "ERROR! Mutex init error.\n"
# define CREATING_TABLE_ERROR "ERROR! Table create error.\n"
# define START_SIMULATION_ERROR "ERROR! Start simulation error.\n"

# define ERROR 1
# define SUCCESS 0

typedef struct s_philo
{
	pthread_t		thread_id;
	int				philo_id;
	int				amount_eaten;
	int				fork_left;
	int				fork_right;
	uint64_t time_last_meal;
	struct s_table	*table;
}					t_philo;

typedef struct s_table
{
	t_philo			*philo;
	uint64_t		time_to_die;
	int				total_philo;
	int				eating_time;
	int				sleeping_time;
	int				meals_limit;
	int				is_there_death;
	uint64_t		time_of_death;
	int				id_of_deceased;
	int				check_meal_count;
	int				num;
	uint64_t		start_time;
	pthread_mutex_t	m_with_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_die;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_eat;
}					t_table;

// init_table
void				init_philo(t_table *table);
int					init_mutex(t_table *table);
int					init_table(t_table *table, char **av);
int					creating_table(t_table *table);
// simulation
int					create_threads(t_table *table);
int					monitor_threads(t_table *table, int i);
int					start_simulation(t_table *table);
// threads_start
int					check_dead_function(t_table *table, t_philo *philo);
int					grab_left_fork(t_table *table, t_philo *philo);
int					perform_eating(t_table *table, t_philo *philo);
int					manage_life(t_table *table, t_philo *philo);
void				*philo_life(void *arg);
// ultis
void				print_message(t_table *philo, char *str, int number,
						int flag);
uint64_t			get_time(void);
void				milisleep(uint64_t time);
int					philo_atoi(char *str);
// cleanup
void				destroy_mutex(t_table *table, int num);
void				free_malloc(t_table *table);

#endif
