#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

// Defines

#define TRUE 1
#define FALSE 0
#define MAX_PHILOS 200

/* ===== Philosopher State Flags ===== */

#define FORK_TAKEN 5
#define EATING 6
#define SLEEPING 7
#define THINKING 8
#define DEAD 9

typedef struct s_philos
{
	int					id;
	int					last_meal;
	int					meals_had;
	int					is_alive;
	pthread_mutex_t		lock;
	pthread_mutex_t		right_fork;
	pthread_mutex_t		*left_fork;
	const struct s_data	*data;
}				t_philos;

typedef struct s_table
{
	t_philos			*philos;
	pthread_mutex_t		*forks;
	pthread_mutex_t		death_flag;
	pthread_mutex_t		finished_eating;
	const struct s_data	*data;
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

//				FUNCTIONS

void	execute_cmd(t_data *data, char **envp);
int		argc_check(int argc);
void	check_in_file(t_data *data, int fdin);
int		philo_check(t_philos *philo);
int		get_time(void);

//				INIT FUNCS

void	setup_root(t_root **root, int argc, char **argv);

// ============= MONITORING ===============

int	monitoring(t_table *table);
int	check_if_meal_is_done(t_table *table);
int	look_for_dead_philos(t_table *table);
int	philo_check(t_philos *philo);

// =============== ROUTINE =================

void	routine(t_philos *philo, t_table *table);
void	eat(t_philos *philo);
void	sleep_and_think(t_philos *philo);

//				UTIL FUNCS

void	ft_usleep(int milliseconds);
void	write_state(t_philos *philo, int state);
int		ft_strcmp(char *s1, char *s2);
int		atoi(char *str);
int		digit_check(char *str);

//				PARSING
int	check_parsing(t_root *root, int argc, char **argv);

#endif
