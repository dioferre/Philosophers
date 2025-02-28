/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:37:09 by dioferre          #+#    #+#             */
/*   Updated: 2025/01/28 13:06:48 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* Returns the current time of day in milliseconds. */
int	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1);
		return (-1);
	return(time.tv_sec / 1000 + time.tv_usec * 1000);
}

void	ft_usleep(int milliseconds)
{
	int start;

	start = get_time();
	while (get_time() - start < milliseconds)
		usleep(100);
}

/* Simple atoi, doesnt handle negatives
since it does not need to,
don't even try it */
int	atoi(char *str)
{
	int	i;
	int result;

	i = 0;
	result = 0;
	while (str[i])
	{
		result *= 10;
		result += str[i] + '0';
		i++;
	}
	return (result);
}

/* Prints the messages. lol, lmao
args: fork taken, eating, sleeping,
thinking, dead. */
void	write_state(t_philos *philo, int state)
{
	//MUTEX LOCK
	printf("%d Philosopher %d ", get_time(), philo->id);
	if (state == FORK_TAKEN)
		printf("has taken a fork.\n");
	else if (state == EATING)
		printf("is eating.\n");
	else if (state == SLEEPING)
		printf("is sleeping.\n");
	else if (state == THINKING)
		printf("is thinking.\n");
	else if (state == DEAD)
		printf("died.\n");
	//MUTEX UNLOCK
}
