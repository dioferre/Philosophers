/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:10:44 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/28 10:21:41 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	setup_root(t_root **root, int argc, char **argv)
{
	(*root)->data = init_data(argc, argv);
	(*root)->table = init_table((*root)->data, argv);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->nr_philos = atoi(argv[1]);
	data->time2die = atoi(argv[2]);
	data->time2eat = atoi(argv[3]);
	data->time2sleep = atoi(argv[4]);
	if (argc == 6)
		data->nr_meals = atoi(argv[5]);
	return (data);
}

t_table	*init_table(t_data *data, char **argv)
{
	pthread_mutex_t	forks[data->nr_philos];
	t_table			*table;

	table = malloc(sizeof(t_table));
	table->forks = &forks;
	table->data = data;
	return (table);
}
