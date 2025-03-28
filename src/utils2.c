/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 09:17:14 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 13:36:11 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_check_values(t_philos *philo)
{
	printf("---------------------------\n");
	printf("time: |%zu|\n", get_time());
	printf("table start: |%zu|\n",  philo->table->start_time);
	printf("philo last meal: |%zu|\n",  philo->last_meal);
	printf("time to die: |%zu|\n",  (size_t)philo->data->time2die);
	if (philo->last_meal == 0)
		printf("result: |%lu|\n", (get_time() - philo->table->start_time));
	else
		printf("result: |%lu|\n", (get_time() - philo->last_meal));
	printf("---------------------------\n");
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

int	check_status(t_philos *philo)
{
	if (philo->last_meal == 0)
	{
		if (get_time() - philo->table->start_time > (size_t) philo->data->time2die)
			return (kill_and_write_state(philo), DEAD);
	}
	else if (get_time() - philo->last_meal > (size_t) philo->data->time2die)
	{
		return (kill_and_write_state(philo), DEAD);
	}
	return (ALIVE);
}

int	is_philosopher_dead(t_philos *philo)
{
//	print_check_values(philo);
	if (philo->last_meal == 0)
	{
		if (get_time() - philo->table->start_time > (size_t)philo->data->time2die)
			return (kill_and_write_state(philo), 1);
	}
	else if (get_time() - philo->last_meal > (size_t)philo->data->time2die)
			return (kill_and_write_state(philo), 1);
	return (0);
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
