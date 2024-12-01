/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 18:35:46 by imatek            #+#    #+#             */
/*   Updated: 2024/11/29 12:17:11 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!ft_getter(&philo->data->data_mutex, &philo->data->ready))
	{
		usleep(50);
	}
	if (philo->data->nb_philo == 1)
		ft_solo_philo(philo);
	if (philo->position % 2 == 0)
		usleep(1500);
	while (!ft_getter(&philo->data->data_mutex, &philo->data->dead))
	{
		ft_eat(philo);
		if (ft_getter(&philo->philo_mutex, &philo->full))
			break ;
		ft_print(philo, "is sleeping\n");
		ft_usleep(philo, philo->time_to_sleep);
		ft_print(philo, "is thinking\n");
		if (philo->data->nb_philo % 2 == 1)
			ft_usleep(philo, (philo->time_to_eat * 2 - philo->time_to_sleep)
				* 0.5);
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
				&data->philo[i]))
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
	if (ft_getter(&data->data_mutex, &data->dead) == 0)
		ft_setter(&data->data_mutex, &data->all_full, 1);
	pthread_join(data->supervise, NULL);
}
