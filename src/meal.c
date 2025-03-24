/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:46 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/24 16:03:52 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ola_function(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	pthread_mutex_lock(philo->printex);
	printf("|%zi| Philosopher id %d says 'ola!'\n", get_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(philo->printex);
	return (arg);
}

int	start_meal(t_table *table, t_philos *philos)
{
	int	i;
	size_t	start_time;
	(void) table;
	i = 0;
	start_time = get_time();
	while (i < philos->data->nr_philos)
	{
		philos[i].start_time = start_time;
		if (pthread_create(&philos[i].thread, NULL,
				ola_function, &philos[i]) != 0)
			write(2, "TError\n", 7);
		i++;
	}
	i = 0;
	while (i < philos->data->nr_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	printf("done!\n");
	return (1);
}
