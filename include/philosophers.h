/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dioferre <dioferre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 15:10:13 by dioferre          #+#    #+#             */
/*   Updated: 2025/03/29 15:10:47 by dioferre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

/* ============ |DEFINES| ============ */

# define FALSE 0
# define TRUE 1

# define MAX_PHILOS 200

// Philosopher states

# define DEAD 0
# define ALIVE 1
# define FORK_TAKEN 5
# define EATING 6
# define SLEEPING 7
# define THINKING 8

/* ============ |STRUCTS| ============ */

typedef struct s_philos
{
	int						id;
	int						meals_had;
	size_t					start_time;
	size_t					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*last_meal_lock;
	pthread_mutex_t			*meal_lock;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	const struct s_data		*data;
	struct s_table			*table;
}				t_philos;

typedef struct s_table
{
	int						death_flag;
	size_t					start_time;
	pthread_t				thread;
	t_philos				*philos;
	pthread_mutex_t			*printex;
	pthread_mutex_t			*forks;
	pthread_mutex_t			*death_flag_lock;
	const struct s_data		*data;
}				t_table;

typedef struct s_data
{
	int	nr_philos;
	int	nr_meals;
	int	time2die;
	int	time2eat;
	int	time2sleep;
}				t_data;

typedef struct s_root
{
	t_data	*data;
	t_table	*table;
}				t_root;

/* ============= |FUNCTIONS| ============= */

// ============== SETUP =================

int			check_parsing(int argc, char **argv);

void		setup_root(t_root **root, int argc, char **argv);
void		create_philo(t_table *table, t_philos *philo,
				pthread_mutex_t *forks, int i);

t_data		*init_data(int argc, char **argv);
t_table		*init_table(t_data *data);

// ============== ROUTINE =================

int			start_meal(t_table *table, t_philos *philos);

int			eat(t_philos *philo);
int			philo_sleep(t_philos *philo);
void		*routine(void *arg);

// ============= MONITORING ===============

void		*monitor(void *arg);
int			check_death_flag(t_philos *philo);
int			get_status(t_philos *philo);
void		kill_and_write_state(t_philos *philo);

// ============== UTILS =================

size_t		get_time(void);
void		ft_usleep(size_t milliseconds);

int			ft_strcmp(char *s1, char *s2);
int			ft_itoa(char *str);
int			digit_check(char *str);

void		write_state(t_philos *philo, int state);
void		pick_up_forks(t_philos *philo);
void		drop_forks(t_philos *philo);

void		kill_root(t_root *root);

#endif
