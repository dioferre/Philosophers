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
	while (TRUE)
	{
		if (check_if_meal_is_done || look_for_dead_philos)
			break;
	}
	return (1);
}

int	is_philosopher_dead(t_philos *philo)
{
	if (get_time() - philo->last_meal > philo->data->time2die)
	{
		philo->is_alive = 0;
		return (1);
	}
	return (0);
}

int	check_if_meal_is_done(t_table *table)
{
	int	i;
	int	philos_finished;

	i = 0;
	philos_finished = 0;
	while (i < table->data->nr_philos)
	{
		pthread_mutex_lock(&table->philos[i].lock);
		if (&table->philos[i].meals_had == table->data->nr_meals)
			philos_finished++;
		pthread_mutex_unlock(&table->philos[i].lock);
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
		pthread_mutex_lock(&table->philos[i].lock);
		if (is_philosopher_dead(&table->philos[i])) // have to make a function to check if philo is dead here.
		{
			write_state(&table->philos, DEAD);
			pthread_mutex_unlock(&table->philos[i].lock);
			return (1);
		}
		pthread_mutex_unlock(&table->philos[i].lock);
		i++;
	}
	return (0);
}

int	philo_check(t_philos *philo)
{
	pthread_mutex_lock(&philo->lock);
	if (!(&philo->is_alive))
	{
		pthread_mutex_unlock(&philo->lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->lock);
	return (1);
}
