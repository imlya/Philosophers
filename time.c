/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 19:00:31 by imatek            #+#    #+#             */
/*   Updated: 2024/11/19 19:07:08 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_gettime(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(t_philo *philo, long time)
{
	long	start_time;
	long	elapsed_time;
	long	remaining_time;

	start_time = ft_gettime();
	while (ft_gettime() - start_time < time)
	{
		if (ft_getter(&philo->data->dead_mutex, &philo->data->dead))
			return ;
		elapsed_time = ft_gettime() - start_time;
		remaining_time = time - elapsed_time;
		if (remaining_time > 50)
			usleep(remaining_time / 2);
		else
		{
			while (ft_gettime() - start_time < time)
				;
		}
	}
	return ;
}
