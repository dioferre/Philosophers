/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:46 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/28 09:45:01 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ola_function(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	printf("|%zi| Philosopher id %d says 'ola!'\n", get_time() - philo->table->start_time, philo->id);
	return (arg);
}

int	start_meal(t_table *table, t_philos *philos)
{
	int	i;

	i = 0;
	table->start_time = get_time();
	while (i < philos->data->nr_philos)
	{
		if (pthread_create(&philos[i].thread, NULL,
				routine, &philos[i]) != 0)
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
