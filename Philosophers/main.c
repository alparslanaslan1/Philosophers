/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:33:16 by alaslan           #+#    #+#             */
/*   Updated: 2024/07/09 17:47:19 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac < 5 || ac > 6)
		err_exit("missing or too many arguments entered.");
	if (creating_table(&table, av) != SUCCESS)
		return (err_exit(CREATING_TABLE_ERROR), destroy_mutex(&table,
				table.num), ERROR);
	if (start_simulation(&table))
		return (err_exit(START_SIMULATION_ERROR), destroy_mutex(&table,
				table.total_philo + 5), ERROR);
	return (destroy_mutex(&table, table.total_philo + 5), SUCCESS);
}
