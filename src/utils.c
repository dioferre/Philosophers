/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:09 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 17:54:26 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Returns the current time of day in milliseconds. */
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("Time error\n") ,-1);
	return(time.tv_sec * 1000 + time.tv_usec / 1000);
}
/* Precise usleep for accuracy. */
void	ft_usleep(size_t milliseconds)
{
	size_t start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(100);
}

/* Checks if a string has ONLY digits,
returns 0 if not, 1 if yes */
int	digit_check(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!(str[i] >= '0' && str[i] <= '9'))
			return(0);
	return (1);
}

/* Simple itoa, doesnt handle negatives
since it does not need to,
don't even try it */
int	ft_itoa(char *str)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result *= 10;
		result += str[i] - '0';
		i++;
	}
	return (result);
}

/* Prints the messages. lol, lmao
args: fork taken, eating, sleeping,
thinking, dead. */
void	write_state(t_philos *philo, int state)
{
	pthread_mutex_lock(philo->table->printex);
	pthread_mutex_lock(philo->table->death_flag_lock);
	if (philo->table->death_flag == FALSE)
	{
		printf("%zi %d ", get_time() - philo->table->start_time, philo->id);
		if (state == FORK_TAKEN)
			printf("has taken a fork\n");
		else if (state == EATING)
			printf("is eating\n");
		else if (state == SLEEPING)
			printf("is sleeping\n");
		else if (state == THINKING)
			printf("is thinking\n");
	}
	else if (state == DEAD)
		printf("%zi %d died\n", get_time() - philo->table->start_time, philo->id);
	pthread_mutex_unlock(philo->table->printex);
	pthread_mutex_unlock(philo->table->death_flag_lock);
}
