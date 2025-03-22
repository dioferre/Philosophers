/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:22:38 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/28 13:06:39 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	routine(t_philos *philo, t_table *table)
{
	(void) table;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (TRUE)
	{
		if (is_philosopher_dead(philo))
		{
			write_state(philo, DEAD);
			break;
		}
		eat(philo);
		if (philo->meals_had == philo->data->nr_meals)
			break;
		sleep_and_think(philo);
	}
}

void	eat(t_philos *philo)
{
	pthread_mutex_lock(&philo->left_fork);
	write_state(philo, FORK_TAKEN); 
	pthread_mutex_lock(philo->right_fork);
	write_state(philo, FORK_TAKEN);
	write_state(philo, EATING);
	philo->meals_had++;
	ft_usleep(philo->data->time2eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	sleep_and_think(t_philos *philo)
{
	write_state(philo, SLEEPING);
	ft_usleep(philo->data->time2sleep);
	write_state(philo, THINKING);
}
