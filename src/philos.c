/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:22:38 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/25 20:14:27 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	is_philosopher_dead(t_philos *philo)
{
	if (get_time() - philo->last_meal > (size_t)philo->data->time2die)
	{
		pthread_mutex_lock(philo->statustex);
		pthread_mutex_lock(philo->table->death_flag);
		philo->status = DEAD;
		pthread_mutex_unlock(philo->statustex);
		pthread_mutex_unlock(philo->table->death_flag);
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (TRUE)
	{
		if (eat(philo) ==  -1)
			break;
		if (philo->meals_had == philo->data->nr_meals)
			break;
		sleep_and_think(philo);
	}
	return (arg);
}

int	eat(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	write_state(philo, FORK_TAKEN);
	pthread_mutex_lock(philo->right_fork);
	write_state(philo, FORK_TAKEN);
	write_state(philo, EATING);
	if (is_philosopher_dead(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (-1);
	}
	philo->meals_had++;
	philo->last_meal = get_time();
	ft_usleep(philo->data->time2eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

void	sleep_and_think(t_philos *philo)
{
	write_state(philo, SLEEPING);
	ft_usleep(philo->data->time2sleep);
	write_state(philo, THINKING);
}
