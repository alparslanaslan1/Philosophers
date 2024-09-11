/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:25:40 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/12 01:29:29 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	init_philo(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->total_philo)
	{
		table->philo[i].philo_id = i + 1;
		table->philo[i].amount_eaten = 0;
		table->philo[i].fork_left = i;
		table->philo[i].fork_right = (i + 1) % table->total_philo;
		table->philo[i].time_last_meal = table->start_time;
		table->philo[i].table = table;
	}
}

int	init_mutex(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->total_philo)
		if (pthread_mutex_init(&table->forks[i], NULL) != SUCCESS)
			return (table->num = i, ERROR);
	if (pthread_mutex_init(&table->m_print, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR), table->num = table->total_philo,
			ERROR);
	if (pthread_mutex_init(&table->m_die, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR), table->num = table->total_philo + 1,
			ERROR);
	if (pthread_mutex_init(&table->m_time, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR), table->num = table->total_philo + 2,
			ERROR);
	if (pthread_mutex_init(&table->m_eat, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR), table->num = table->total_philo + 3,
			ERROR);
	if (pthread_mutex_init(&table->m_with_eat, NULL) != SUCCESS)
		return (printf(MUTEX_INIT_ERROR), table->num = table->total_philo + 4,
			ERROR);
	return (SUCCESS);
}

int init_table(t_table *table, char **av)
{
	table->total_philo = philo_atoi(av[1]);
	table->time_to_die = philo_atoi(av[2]);
	table->eating_time = philo_atoi(av[3]);
	table->sleeping_time = philo_atoi(av[4]);
	table->meals_limit = -1;
	table->is_there_death = 0;
	table->check_meal_count = 0;
	table->num = 0;
	table->start_time = get_time();
	table->philo = NULL;
	if (av[5])
		table->meals_limit = philo_atoi(av[5]);
	if (table->total_philo == 0 || table->time_to_die == 0
		|| table->eating_time == 0 || table->sleeping_time == 0
		||(av[5] && table->meals_limit == 0))
		return (ERROR);
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
		* table->total_philo);
	if (!table->forks)
		return (ERROR);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->total_philo);
	if (!table->philo)
		return (printf(M_ERROR), ERROR);
	return (init_philo(table), SUCCESS);
}

