/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:22:38 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 13:53:32 by dioferre         ###   ########.fr       */
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

void	*routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	if (philo->data->nr_philos == 1)
		return(one_philo_case(philo), arg);
	while (philo->meals_had != philo->data->nr_meals && !check_death_flag(philo))
	{

		if (eat(philo) == -1)
			break;
		if (philo->meals_had == philo->data->nr_meals)
			break;
		if (sleep_and_think(philo) == -1)
			break;
	}
	return (arg);
}

int	eat(t_philos *philo)
{
	size_t	meal_start_time;

	if (check_death_flag(philo) == TRUE)
		return(-1);
	pick_up_forks(philo);
	write_state(philo, EATING);
	if ((check_death_flag(philo) == TRUE) || is_philosopher_dead(philo))
		return(drop_forks(philo), -1);
	meal_start_time = get_time();
	while(get_time() - meal_start_time < (size_t) philo->data->time2eat)
	{
		if (check_status(philo) == DEAD)
			return (drop_forks(philo), -1);
	}
	philo->last_meal = get_time();
	philo->meals_had++;
	drop_forks(philo);
	if (is_philosopher_dead(philo))
		return (-1);
	return (0);
}

int	sleep_and_think(t_philos *philo)
{
	if (check_death_flag(philo) == TRUE)
		return (-1);
	write_state(philo, SLEEPING);
	ft_usleep(philo->data->time2sleep);
	if (check_death_flag(philo) == TRUE)
		return (-1);
	write_state(philo, THINKING);
	return (0);
}
