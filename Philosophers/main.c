/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alpaslan <alpaslan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:33:16 by alaslan           #+#    #+#             */
/*   Updated: 2024/09/11 00:59:32 by alpaslan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
	{
		printf("missing or too many arguments entered.");
		return (ERROR);
	}
	if (init_table(&table, av) != SUCCESS)
	{
		printf(CHECK_ARGS);
		return (ERROR);
	}
	if (creating_table(&table) != SUCCESS)
	{
		printf(CREATING_TABLE_ERROR);
		destroy_mutex(&table, table.num);
		return (ERROR);
	}
	if (start_simulation(&table))
		return (printf(START_SIMULATION_ERROR), destroy_mutex(&table,
				table.total_philo + 5), ERROR);
	return (destroy_mutex(&table, table.total_philo + 5), SUCCESS);
}
