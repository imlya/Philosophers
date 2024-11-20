/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_getter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:28 by imatek            #+#    #+#             */
/*   Updated: 2024/11/19 20:01:46 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_getter(pthread_mutex_t *mutex, long *variable)
{
	long	value;

	pthread_mutex_lock(mutex);
	value = *variable;
	pthread_mutex_unlock(mutex);
	return (value);
}

void	ft_setter(pthread_mutex_t *mutex, long *variable, long new)
{
	pthread_mutex_lock(mutex);
	*variable = new;
	pthread_mutex_unlock(mutex);
}
