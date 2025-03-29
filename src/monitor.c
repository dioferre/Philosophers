/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 18:01:38 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/29 14:19:55 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_if_meal_done(t_philos *philo)
{
	int	i;
	int	meals_done;

	i = 0;
	meals_done = 0;
	if (philo->data->nr_meals < 0)
		return (0);
	i = 0;
	meals_done = 0;
	while (i < philo->data->nr_philos)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].meals_had >= philo->data->nr_meals)
			meals_done++;
		pthread_mutex_unlock(philo[i].meal_lock);
		i++;
	}
	if (meals_done == philo->data->nr_philos)
		return (-1);
	return (0);
}

int	check_for_dead_philos(t_philos *philo)
{
	int	i;

	i = 0;
	if (philo->data->nr_philos < 2)
		return (-1);
	while (i < philo->data->nr_philos)
	{
		if (get_status(&philo[i]) == DEAD)
			return (-1);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (TRUE)
	{
		if (check_for_dead_philos(table->philos) == -1
			|| check_if_meal_done(table->philos) == -1)
			break ;
	}
	return (arg);
}
