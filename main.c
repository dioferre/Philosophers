/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:52:20 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/29 14:51:29 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_root	*root;

	root = malloc(sizeof(t_root));
	if (check_parsing(argc, argv) != 0)
		return (write(2, "ERROR: Invalid Input\n", 22), free(root), -1);
	setup_root(&root, argc, argv);
	start_meal(root->table, root->table->philos);
	kill_root(root);
}

int	start_meal(t_table *table, t_philos *philos)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	if (pthread_create(&table->thread, NULL,
			monitor, table) != 0)
		write(2, "Thread Error\n", 13);
	while (i < philos->data->nr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				routine, &philos[i]) != 0)
			write(2, "Thread Error\n", 13);
		i++;
	}
	i = 0;
	while (i < philos->data->nr_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	pthread_join(table->thread, NULL);
	return (1);
}
