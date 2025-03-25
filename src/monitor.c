/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:44:24 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/25 20:09:35 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*monitoring(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if (table->data->nr_meals == -1)
	{
		// This needs to be rebuilt, initial idea was to iterate through all philos and check for a dead one,
		// it is however unecessary, Im thinking of just setting a death flag when someone dies and it returing
		// and stopping the simulation.
		while (TRUE)
		{
			if (look_for_dead_philos(table))
				break;
		}
	}
/* 	else
	{
		while (TRUE)
		{
			if (check_if_meal_is_done(table) || look_for_dead_philos(table))
				break;
		}
	} */
	return (arg);
}

/* int	check_if_meal_is_done(t_table *table)
{
	int	i;
	int	philos_finished;

	i = 0;
	philos_finished = 0;
	while (i < table->data->nr_philos)
	{
		pthread_mutex_lock(&table->philos[i].meals_had);
		if (&table->philos[i].meals_had == table->data->nr_meals)
			philos_finished++;
		pthread_mutex_unlock(&table->philos[i].meals_had);
		i++;
	}
	if (philos_finished == table->data->nr_meals)
		return (1);
	return (0);
} */
int	look_for_dead_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->nr_philos)
	{
		pthread_mutex_lock(table->philos[i].statustex);
		if (table->philos[i].status == DEAD)
		{
			pthread_mutex_unlock(table->philos[i].statustex);
			write_state(&table->philos[i], DEAD);
			pthread_mutex_lock(table->death_flag);
			return (1);
		}
		pthread_mutex_unlock(table->philos[i].statustex);
		i++;
	}
	return (0);
}

