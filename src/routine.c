/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:22:38 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/29 15:09:48 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	one_philo_case(t_philos *philo)
{
	pthread_mutex_lock(philo->left_fork);
	write_state(philo, FORK_TAKEN);
	pthread_mutex_unlock(philo->left_fork);
	ft_usleep(philo->data->time2die);
	printf("%zi %d ", get_time() - philo->table->start_time, philo->id);
	printf("died\n");
	return ;
}

void	think(t_philos *philo)
{
	write_state(philo, THINKING);
}

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	if (philo->data->nr_philos == 1)
		return (one_philo_case(philo), arg);
	if (philo->data->nr_meals == 0)
		return (arg);
	while (!check_death_flag(philo))
	{
		think(philo);
		if (eat(philo) == -1)
			break ;
		pthread_mutex_lock(philo->meal_lock);
		if (philo->meals_had == philo->data->nr_meals)
			return (pthread_mutex_unlock(philo->meal_lock), arg);
		pthread_mutex_unlock(philo->meal_lock);
		if (philo_sleep(philo) == -1)
			break ;
		usleep(50);
	}
	return (arg);
}

int	eat(t_philos *philo)
{
	if (check_death_flag(philo) == TRUE)
		return (-1);
	pick_up_forks(philo);
	if (check_death_flag(philo) == TRUE || get_status(philo) == DEAD)
		return (drop_forks(philo), -1);
	write_state(philo, EATING);
	pthread_mutex_lock(philo->last_meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->last_meal_lock);
	while (get_time() - philo->last_meal < (size_t) philo->data->time2eat)
	{
		if (get_status(philo) == DEAD)
			return (drop_forks(philo), -1);
		usleep(50);
	}
	pthread_mutex_lock(philo->meal_lock);
	philo->meals_had++;
	pthread_mutex_unlock(philo->meal_lock);
	drop_forks(philo);
	if (get_status(philo) == DEAD)
		return (-1);
	return (0);
}

int	philo_sleep(t_philos *philo)
{
	if (check_death_flag(philo) == TRUE)
		return (-1);
	write_state(philo, SLEEPING);
	ft_usleep(philo->data->time2sleep);
	return (0);
}
