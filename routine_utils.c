/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 12:22:16 by imatek            #+#    #+#             */
/*   Updated: 2024/11/28 15:17:28 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	if (ft_getter(&philo->data->data_mutex, &philo->data->dead))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %ld %s", (ft_gettime() - philo->data->start), philo->position,
		str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void	ft_solo_philo(t_philo *philo)
{
	if (philo->data->nb_philo == 1)
	{
		ft_take_forks(philo, philo->right_fork, philo->left_fork);
		while (!ft_getter(&philo->data->data_mutex, &philo->data->dead))
			;
	}
}
