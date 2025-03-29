/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:17:14 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/29 15:08:38 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death_flag(t_philos *philo)
{
	int	status;

	status = 0;
	pthread_mutex_lock(philo->table->death_flag_lock);
	if (philo->table->death_flag == TRUE)
		status = 1;
	pthread_mutex_unlock(philo->table->death_flag_lock);
	return (status);
}

void	kill_and_write_state(t_philos *philo)
{
	pthread_mutex_lock(philo->table->death_flag_lock);
	if (philo->table->death_flag == FALSE)
	{
		philo->table->death_flag = TRUE;
		pthread_mutex_unlock(philo->table->death_flag_lock);
		write_state(philo, DEAD);
	}
	else
		pthread_mutex_unlock(philo->table->death_flag_lock);
}

int	get_status(t_philos *philo)
{
	pthread_mutex_lock(philo->last_meal_lock);
	if (philo->last_meal == 0)
	{
		if (get_time() - philo->table->start_time
			> (size_t) philo->data->time2die)
			return (pthread_mutex_unlock(philo->last_meal_lock),
				kill_and_write_state(philo), DEAD);
		pthread_mutex_unlock(philo->last_meal_lock);
	}
	else if (get_time() - philo->last_meal > (size_t) philo->data->time2die)
	{
		return (pthread_mutex_unlock(philo->last_meal_lock),
			kill_and_write_state(philo), DEAD);
		pthread_mutex_unlock(philo->last_meal_lock);
	}
	else
		pthread_mutex_unlock(philo->last_meal_lock);
	return (ALIVE);
}

void	pick_up_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		write_state(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->right_fork);
		write_state(philo, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		write_state(philo, FORK_TAKEN);
		pthread_mutex_lock(philo->left_fork);
		write_state(philo, FORK_TAKEN);
	}
}

void	drop_forks(t_philos *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}
