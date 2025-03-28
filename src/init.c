/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:10:44 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 18:46:26 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	setup_root(t_root **root, int argc, char **argv)
{
	(*root)->data = init_data(argc, argv);
	(*root)->table = init_table((*root)->data);
}

t_data	*init_data(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->nr_philos = ft_itoa(argv[1]);
	data->time2die = ft_itoa(argv[2]);
	data->time2eat = ft_itoa(argv[3]);
	data->time2sleep = ft_itoa(argv[4]);
	if (argc == 6)
		data->nr_meals = ft_itoa(argv[5]);
	else
		data->nr_meals = -1;
	return (data);
}

void	create_philo(t_table *table, t_philos *philo,
			pthread_mutex_t *forks, int i)
{
	philo->data = table->data;
	philo->table = table;
	philo->id = i;
	philo->last_meal = 0;
	philo->meals_had = 0;
	philo->start_time = 0;
	philo->left_fork = &forks[i];
	philo->meal_tex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(philo->meal_tex, NULL);
	if (i - 1 < 0)
		philo->right_fork = &forks[table->data->nr_philos - 1];
	else
		philo->right_fork = &forks[i - 1];
}

t_table	*init_table(t_data *data)
{
	pthread_mutex_t	*forks;
	t_philos		*philos;
	t_table			*table;
	int				i;

	table = malloc(sizeof(t_table));
	table->printex = malloc(sizeof(pthread_mutex_t));
	forks = malloc(data->nr_philos * (sizeof(pthread_mutex_t)));
	philos = malloc(data->nr_philos * (sizeof(t_philos)));
	table->data = data;
	i = -1;
	while (++i < data->nr_philos)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data->nr_philos)
		create_philo(table, &philos[i], forks, i);
	table->forks = forks;
	table->philos = philos;
	table->death_flag = FALSE;
	table->death_flag_lock = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->death_flag_lock, NULL);
	pthread_mutex_init(table->printex, NULL);
	return (table);
}

void	kill_root(t_root *root)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(root->table->death_flag_lock);
	pthread_mutex_destroy(root->table->printex);
	while (i < root->data->nr_philos)
	{
		pthread_mutex_destroy(root->table->philos[i].meal_tex);
		pthread_mutex_destroy(root->table->philos[i].left_fork);
		free(root->table->philos[i].meal_tex);
		i++;
	}
	free(root->table->forks);
	free(root->table->philos);
	free(root->table->printex);
	free(root->table->death_flag_lock);
	free(root->table);
	free(root->data);
	free(root);
}
