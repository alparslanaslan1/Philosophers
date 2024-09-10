/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:58:44 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/11 00:59:19 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	free_malloc(t_table *table)
{
	if (table->philo != NULL)
		free(table->philo);
	if (table->forks != NULL)
		free(table->forks);
}

void	destroy_mutex(t_table *table, int num)
{
	int	i;

	i = -1;
	while (++i < table->total_philo && i < num)
		pthread_mutex_destroy(&table->forks[i]);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_print);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_die);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_time);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_eat);
	if (i++ < num)
		pthread_mutex_destroy(&table->m_with_eat);
	free_malloc(table);
}
