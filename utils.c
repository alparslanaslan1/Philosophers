/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:33:52 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/17 13:47:36 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

void	print_message(t_table *table, char *str, int number, int flag)
{
	pthread_mutex_lock(&table->m_time);
	if (flag == 1)
		printf("%llu %d %s\n", get_time() - table->start_time, number, str);
	if (flag == 2)
		printf("%llu %d is died\n", table->time_of_death,
			table->id_of_deceased);
	pthread_mutex_unlock(&table->m_time);
}

uint64_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) != 0)
	{
		return (ERROR);
	}
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	milisleep(uint64_t time)
{
	uint64_t	start;

	start = get_time() + time;
	while (get_time() < start)
		usleep(250);
}

int	philo_atoi(char *str)
{
	int		i;
	long	res;

	i = 0;
	res = 0;
	if (!str)
		return (0);
	while (str[i] <= 32)
		i++;
	if (str[i] == '+')
		i++;
	while ((str[i] >= '0' && str[i] <= '9') || str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		res = res * 10;
		res = res + str[i] - 48;
		i++;
		if (res > 2147483647 || res == 0)
			return (0);
	}
	return (res);
}
