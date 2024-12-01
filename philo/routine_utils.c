/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:22:16 by imatek            #+#    #+#             */
/*   Updated: 2024/12/01 21:47:27 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (ft_getter(&philo->data->data_mutex, &philo->data->dead))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return ;
	}
	printf("%ld %ld %s", (ft_gettime() - philo->data->start), philo->position,
		str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	ft_solo_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, "has taken a fork\n");
		while (!ft_getter(&philo->data->data_mutex, &philo->data->dead))
			usleep(10);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (0);
}
