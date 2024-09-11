/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_start.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:33:47 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/12 01:47:26 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	check_dead_function(t_table *table, t_philo *philo)
{
	uint64_t	current_time;
	uint64_t	last_eat;

	pthread_mutex_lock(&table->m_time);
	current_time = get_time();
	last_eat = philo->time_last_meal;
	pthread_mutex_unlock(&table->m_time);
	if (current_time - last_eat >= table->time_to_die)
	{
		pthread_mutex_lock(&table->m_die);
		table->is_there_death = 1;
		table->time_of_death = current_time - table->start_time;
		pthread_mutex_unlock(&table->m_die);
		return (ERROR);
	}
	return (SUCCESS);
}

int	perform_eating(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->fork_right]);
	pthread_mutex_lock(&table->m_die);
	if (table->is_there_death == 1)
	{
		pthread_mutex_unlock(&table->m_die);
		pthread_mutex_unlock(&table->forks[philo->fork_left]);
		pthread_mutex_unlock(&table->forks[philo->fork_right]);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->m_die);
	print_message(table, "has taken a right chopStick.", philo->philo_id, 1);
	print_message(table, "is eating.", philo->philo_id, 1);
	milisleep(table->eating_time);
	pthread_mutex_lock(&table->m_time);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&table->m_time);
	pthread_mutex_lock(&table->m_with_eat);
	philo->amount_eaten++;
	pthread_mutex_unlock(&table->m_with_eat);
	pthread_mutex_unlock(&table->forks[philo->fork_left]);
	pthread_mutex_unlock(&table->forks[philo->fork_right]);
	return (SUCCESS);
}

int	grab_left_fork(t_table *table, t_philo *philo)
{
	pthread_mutex_lock(&table->forks[philo->fork_left]);
	pthread_mutex_lock(&table->m_die);
	if (table->is_there_death == 1)
	{
		pthread_mutex_unlock(&table->m_die);
		pthread_mutex_unlock(&table->forks[philo->fork_left]);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->m_die);
	print_message(table, "has taken a left chopStick.", philo->philo_id, 1);
	if (table->total_philo == 1)
	{
		pthread_mutex_unlock(&table->forks[philo->fork_left]);
		pthread_mutex_lock(&table->m_die);
		while (table->is_there_death != 1)
		{
			pthread_mutex_unlock(&table->m_die);
			pthread_mutex_lock(&table->m_die);
		}
		pthread_mutex_unlock(&table->m_die);
		return (ERROR);
	}
	return (perform_eating(table, philo));
}

int	manage_life(t_table *table, t_philo *philo)
{
	if (grab_left_fork(table, philo) != SUCCESS)
		return (ERROR);
	pthread_mutex_lock(&table->m_die);
	if (table->is_there_death == 1)
	{
		pthread_mutex_unlock(&table->m_die);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->m_die);
	print_message(table, "is sleeping.", philo->philo_id, 1);
	milisleep(table->sleeping_time);
	pthread_mutex_lock(&table->m_die);
	if (table->is_there_death == 1)
	{
		pthread_mutex_unlock(&table->m_die);
		return (ERROR);
	}
	pthread_mutex_unlock(&table->m_die);
	print_message(table, "is thinking.", philo->philo_id, 1);
	return (SUCCESS);
}

void	*philo_life(void *arg)
{
	t_philo	*philo;
	int		continue_life;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2 != 1)
		milisleep(10);
	continue_life = 1;
	while (continue_life)
	{
		if (manage_life(philo->table, philo) == ERROR)
			break ;
		pthread_mutex_lock(&philo->table->m_with_eat);
		if (philo->amount_eaten == philo->table->meals_limit)
		{
			philo->table->check_meal_count++;
			continue_life = 0;
		}
		pthread_mutex_unlock(&philo->table->m_with_eat);
	}
	return (NULL);
}
