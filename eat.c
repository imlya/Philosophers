/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:05:45 by imatek            #+#    #+#             */
/*   Updated: 2024/11/28 12:44:26 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_release_forks(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	if (philo->position % 2 == 0)
	{
		pthread_mutex_unlock(fork1);
		pthread_mutex_unlock(fork2);
	}
	else
	{
		pthread_mutex_unlock(fork2);
		pthread_mutex_unlock(fork1);
	}
}

void	ft_take_forks(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	if (philo->position % 2 == 0)
	{
		pthread_mutex_lock(fork1);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(fork2);
		ft_print(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(fork2);
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_lock(fork1);
		ft_print(philo, "has taken a fork\n");
	}
	if (ft_getter(&philo->data->data_mutex, &philo->data->dead))
		ft_release_forks(philo, philo->left_fork, philo->right_fork);
}

int	ft_eat(t_philo *philo)
{
	ft_take_forks(philo, philo->right_fork, philo->left_fork);
	ft_setter(&philo->last_meal_mutex, &philo->last_meal, ft_gettime());
	philo->nb_eat++;
	ft_print(philo, "is eating\n");
	ft_usleep(philo, philo->time_to_eat);
	ft_release_forks(philo, philo->left_fork, philo->right_fork);
	if (philo->data->must_eat > 0 && philo->nb_eat == philo->data->must_eat)
		ft_setter(&philo->last_meal_mutex, &philo->full, 1);
	return (1);
}
