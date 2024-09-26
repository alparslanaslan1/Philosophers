/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:17:31 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/17 14:49:31 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->total_philo)
	{
		if (pthread_create(&table->philo[i].thread_id, NULL, &philo_life,
				&table->philo[i]))
		{
			while (--i >= 0)
				pthread_join(table->philo[i].thread_id, NULL);
			return (ERROR);
		}
	}
	return (SUCCESS);
}

int	monitor_threads(t_table *table, int i)
{
	int	all_full;

	while (1)
	{
		i = -1;
		all_full = 1;
		while (++i < table->total_philo)
		{
			pthread_mutex_lock(&table->m_with_eat);
			if (check_dead_function(table, &table->philo[i])
				|| table->check_meal_count == table->total_philo)
			{
				pthread_mutex_unlock(&table->m_with_eat);
				table->id_of_deceased = i + 1;
				return (SUCCESS);
			}
			if (table->philo[i].amount_eaten < table->meals_limit
				|| table->meals_limit == -1)
				all_full = 0;
			pthread_mutex_unlock(&table->m_with_eat);
		}
		if (all_full)
			break ;
	}
	return (SUCCESS);
}

static int	wait_threads(t_table *table)
{
	if (create_threads(table) == ERROR)
		return (ERROR);
	return (monitor_threads(table, -1));
}

int	start_simulation(t_table *table)
{
	int	i;

	i = -1;
	if (wait_threads(table))
		return (ERROR);
	while (++i < table->total_philo)
	{
		if (pthread_join(table->philo[i].thread_id, NULL))
			return (ERROR);
	}
	if (table->is_there_death)
		print_message(table, "is died\n", 0, 2);
	return (SUCCESS);
}
