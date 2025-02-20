/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervise.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:26:30 by imatek            #+#    #+#             */
/*   Updated: 2024/12/03 12:14:51 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_check_death(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		if (ft_getter(&data->data_mutex, &data->all_full))
			break ;
		if (ft_getter(&data->philo[i].philo_mutex, &data->philo[i].full))
			continue ;
		if ((ft_gettime() - ft_getter(&data->philo[i].philo_mutex,
					&data->philo[i].last_meal) > data->philo[i].time_to_die))
		{
			ft_print(&data->philo[i], "died\n");
			if (ft_getter(&data->data_mutex, &data->dead))
				break ;
			ft_setter(&data->data_mutex, &data->dead, 1);
			break ;
		}
	}
}

void	*ft_supervise(void *s)
{
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
		ft_check_death(data);
		if (ft_getter(&data->data_mutex, &data->all_full))
		{
			printf("Everybody is full\n");
			break ;
		}
	}
	return (NULL);
}
