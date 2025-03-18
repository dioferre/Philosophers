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
	else
		data->nr_meals = -1;
	return (data);
}

void	create_philo(t_data *data, t_philos *philo, int i)
{
	philo[i].data = data;
	philo[i].id = i;
	pthread_mutex_init(&philo[i].is_alive, NULL);
	pthread_mutex_init(&philo[i].meals_had, NULL);
	philo[i].is_alive = TRUE;
	philo[i].last_meal = 0;
	philo[i].meals_had = 0;
	philo[i].left_fork = NULL;
	philo[i].right_fork = NULL;
}

t_table	*init_table(t_data *data, char **argv)
{
	pthread_mutex_t	forks[data->nr_philos];
	t_philos		philos[data->nr_philos]; 
	t_table			*table;
	int	i;

	i = 0;
	while (i++ < data->nr_philos)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < data->nr_philos) // need to plan this out better lololol
	{
		create_philo(data, &philos[i], i);
		// link both forks
		i++;
	}
	table = malloc(sizeof(t_table));
	table->forks = &forks;
	table->data = data;
	table->philos = philos;
	return (table);
}
