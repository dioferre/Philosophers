#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <unistd.h>

// Defines

#define FALSE 0
#define TRUE 1

#define DEAD 0
#define ALIVE 1

#define MAX_PHILOS 200

/* ===== Philosopher State Flags ===== */

#define FORK_TAKEN 5
#define EATING 6
#define SLEEPING 7
#define THINKING 8


typedef struct s_philos
{
	int						id;
	int						meals_had;
	size_t					start_time;
	size_t					last_meal;
	pthread_t				thread;
	pthread_mutex_t			*left_fork;
	pthread_mutex_t			*right_fork;
	struct s_data		*data;
	struct s_table	*table;
}				t_philos;

typedef struct s_table
{
	int					death_flag;
	size_t				start_time;
	t_philos			*philos;
	pthread_t			thread;
	pthread_mutex_t		*printex;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*death_flag_lock;
	pthread_mutex_t		finished_eating;
	struct s_data	*data;
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
int		start_meal(t_table *table, t_philos *philos);
size_t		get_time(void);

//				INIT FUNCS

void	setup_root(t_root **root, int argc, char **argv);

// ============= MONITORING ===============

void	*monitoring(void *arg);
int	check_if_meal_is_done(t_table *table);
int	look_for_dead_philos(t_table *table);
int	philo_check(t_philos *philo);
int	is_philosopher_dead(t_philos *philo);

// =============== ROUTINE =================

void	*routine(void *arg);
int		eat(t_philos *philo);
int		sleep_and_think(t_philos *philo);

//				UTIL FUNCS


t_data	*init_data(int argc, char **argv);
t_table	*init_table(t_data *data);
void	create_philo(t_table *table, t_philos *philo, pthread_mutex_t *forks, int i);
void	kill_root(t_root *root);
int		check_status(t_philos *philo);

void	pick_up_forks(t_philos *philo);
void	drop_forks(t_philos *philo);


void	ft_usleep(size_t milliseconds);
void	write_state(t_philos *philo, int state);
int		ft_strcmp(char *s1, char *s2);
int		ft_itoa(char *str);
int		digit_check(char *str);
void	kill_root(t_root *root);

//				PARSING
int	check_parsing(t_root *root, int argc, char **argv);

#endif
