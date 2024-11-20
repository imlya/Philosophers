/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:14:53 by imatek            #+#    #+#             */
/*   Updated: 2024/11/20 14:52:17 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_print(t_philo *philo, char *str)
{
	if (ft_getter(&philo->data->dead_mutex, &philo->data->dead))
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %ld %s", (ft_gettime() - philo->data->start), philo->position,
		str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
