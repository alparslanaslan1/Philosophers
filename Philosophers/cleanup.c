/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:58:44 by alaslan           #+#    #+#             */
/*   Updated: 2024/06/10 17:15:15 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	err_exit(char *str)
{
	printf("%s", str);
	exit(0);
}

int	free_malloc(t_table *table)
{
	free(table->philo);
	free(table->forks);
	return (SUCCESS);
}

int	destroy_mutex(t_table *table, int num)
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
	return (free_malloc(table));
}
