/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:44:24 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/28 13:18:19 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	monitoring(t_table *table)
{
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
	else
	{
		while (TRUE)
		{
			if (check_if_meal_is_done(table) || look_for_dead_philos(table))
				break;
		}
	}
	return (1);
}

int	check_if_meal_is_done(t_table *table)
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
}
int	look_for_dead_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->data->nr_philos)
	{
		if (is_philosopher_dead(&table->philos[i]))
		{
			write_state(&table->philos, DEAD);
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_philosopher_dead(t_philos *philo)
{
	if (!philo->is_alive)
		return (1);
	else if (get_time() - philo->last_meal >= philo->data->time2die)
	{
		pthread_mutex_lock(&philo->is_alive);
		philo->is_alive = FALSE;
		pthread_mutex_unlock(&philo->is_alive);
		return (1);
	}
	return (0);
}