#include "philosophers.h"

void	kill_root(t_root *root)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(root->table->death_flag);
	while (i < root->data->nr_philos)
	{
		pthread_mutex_destroy(&root->table->philos[i].last_meal);
		pthread_mutex_destroy(&root->table->philos[i].is_alive);
		pthread_mutex_destroy(&root->table->philos[i].left_fork);
		root->table->philos[i].right_fork = NULL;
		i++;
	}
	free(root->table);
	free(root->data);
}