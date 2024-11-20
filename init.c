/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:04:33 by imatek            #+#    #+#             */
/*   Updated: 2024/11/20 13:53:13 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->fork_mutex = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork_mutex)
		return (NULL, printf("malloc fork error\n"));
	while (++i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork_mutex[i], NULL);
	}
	pthread_mutex_init(&data->ready_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
	return (1);
}

int	ft_init_data(t_data *data, int ac, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!data->philo)
		return (NULL, printf("malloc philo error\n"));
	if (ac == 5)
		data->must_eat = -1;
	else if (ac == 6)
		data->must_eat = ft_atol(av[5]);
	ft_init_mutex(data);
	return (1);
}

int	ft_init_philo(t_data *data, char **av)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		data->philo[i].position = i + 1;
		data->philo[i].time_to_die = ft_atol(av[2]);
		data->philo[i].time_to_eat = ft_atol(av[3]);
		data->philo[i].time_to_sleep = ft_atol(av[4]);
		data->philo[i].data = data;
		data->philo[i].last_meal = ft_gettime();
		data->philo[i].left_fork = &data->fork_mutex[i];
		data->philo[i].right_fork = &data->fork_mutex[data->philo[i].position
			% data->nb_philo];
		pthread_mutex_init(&data->philo[i].last_meal_mutex, NULL);
		pthread_mutex_init(&data->philo[i].full_mutex, NULL);
	}
	return (1);
}
