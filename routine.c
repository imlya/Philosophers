/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Moon <Moon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:35:46 by imatek            #+#    #+#             */
/*   Updated: 2024/11/28 04:43:46 by Moon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (ft_solo_philo(philo))
		return (0);
	while (!ft_getter(&philo->data->data_mutex, &philo->data->ready))
	{
		usleep(10);
	}
	if (philo->position % 2 == 0)
		usleep(50);
	while (!ft_getter(&philo->data->data_mutex, &philo->data->dead))
	{
		if (!ft_eat(philo))
			break ;
		ft_print(philo, "is sleeping\n");
		ft_usleep(philo, philo->time_to_sleep);
		ft_print(philo, "is thinking\n");
		if (philo->position % 2 == 1)
			ft_usleep(philo, (philo->time_to_eat * 2 - philo->time_to_sleep));
	}
	return (NULL);
}

void	*ft_supervise(void *s)
{
	int		i;
	t_data	*data;

	data = (t_data *)s;
	while (!ft_getter(&data->data_mutex, &data->ready))
	{
		usleep(10);
	}
	usleep(data->philo[0].time_to_die * 1000);
	while (1)
	{
		if (ft_getter(&data->data_mutex, &data->dead))
			break ;
		i = -1;
		while (++i < data->nb_philo)
		{
			if(ft_getter(&data->data_mutex, &data->full))
				break ;
			if ((ft_gettime() - ft_getter(&data->philo[i].last_meal_mutex,
						&data->philo[i].last_meal) > data->philo[i].time_to_die))
			{
				ft_print(&data->philo[i], "died\n");
				ft_setter(&data->data_mutex, &data->dead, 1);
				break ;
			}
			else if (ft_getter(&data->data_mutex, &data->full))
			{
				ft_setter(&data->data_mutex, &data->dead, 1);
				break ;
			}

		}
	}
	return (NULL);
}

void	ft_thread(t_data *data)
{
	int	i;

	i = -1;
	data->start = ft_gettime();
	while (++i < data->nb_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, &ft_routine,
				&data->philo[i]) != 0)
		{
			printf("error create\n)");
			return ;
		}
	}
	pthread_create(&data->supervise, NULL, &ft_supervise, data);
	ft_setter(&data->data_mutex, &data->ready, 1);
	i = -1;
	while (++i < data->nb_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
			printf("error join\n");
	}
	if (ft_getter(&data->data_mutex, &data->dead))
	{
		pthread_join(data->supervise, NULL);
		return ;
	}
}
