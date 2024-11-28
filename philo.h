/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:16:13 by imatek            #+#    #+#             */
/*   Updated: 2024/11/28 15:17:38 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	long			dead;
	long			start;
	long			ready;
	long			nb_philo;
	long			must_eat;
	long			all_full;
	pthread_t		supervise;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	data_mutex;
	pthread_mutex_t	print_mutex;
	struct s_philo	*philo;
}					t_data;

typedef struct s_philo
{
	long			position;
	long			nb_eat;
	long			last_meal;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	last_meal_mutex;
	struct s_data	*data;
	long			full;
}					t_philo;

/// INIT ///
int					ft_init_data(t_data *data, int ac, char **av);
int					ft_init_philo(t_data *data, char **av);

/// PARSE ///
long				ft_atol(const char *str);
int					ft_check_digit(char *av);
int					ft_parse(char **av);

/// PRINT ///
void				ft_print(t_philo *philo, char *str);

/// ROUTINE ///
int					ft_eat(t_philo *philo);
void				ft_thread(t_data *data);
void					ft_solo_philo(t_philo *philo);
void				*ft_supervise(void *s);

/// SETTER_GETTER ///
long				ft_getter(pthread_mutex_t *mutex, long *variable);
void				ft_setter(pthread_mutex_t *mutex, long *variable, long new);

/// TIME ///
long				ft_gettime(void);
void				ft_usleep(t_philo *philo, long time);
void				ft_take_forks(t_philo *philo, pthread_mutex_t *fork1,
						pthread_mutex_t *fork2);
#endif
