/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:05:45 by imatek            #+#    #+#             */
/*   Updated: 2024/11/20 14:57:56 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_take_forks(t_philo *philo, pthread_mutex_t *fork1,
		pthread_mutex_t *fork2)
{
	pthread_mutex_lock(fork1);
	ft_print(philo, "has taken a fork\n");
	pthread_mutex_lock(fork2);
	ft_print(philo, "has taken a fork\n");
}

void	ft_release_forks(pthread_mutex_t *fork1, pthread_mutex_t *fork2)
{
	pthread_mutex_unlock(fork1);
	pthread_mutex_unlock(fork2);
}

void	ft_eat(t_philo *philo)
{
	if (philo->data->must_eat == 0)
		return ;
	if (philo->position % 2 == 0)
		ft_take_forks(philo, philo->right_fork, philo->left_fork);
	else
		ft_take_forks(philo, philo->left_fork, philo->right_fork);
	ft_setter(&philo->last_meal_mutex, &philo->last_meal, ft_gettime());
	philo->nb_eat++;
	ft_print(philo, "is eating\n");
	ft_usleep(philo, philo->time_to_eat);
	if (philo->data->must_eat > 0 && philo->nb_eat == philo->data->must_eat)
		ft_setter(&philo->full_mutex, &philo->full, 1);
	if (philo->position % 2 == 0)
		ft_release_forks(philo->left_fork, philo->right_fork);
	else
		ft_release_forks(philo->right_fork, philo->left_fork);
}

// void ft_end_eating(t_philo *philo, pthread_mutex_t *mutex)
// {
//     int i;

//     i = -1;

//     while(++i < philo->data->nb_philo)
//     {
//         if (ft_getter(&philo[i].full_mutex, &philo[i].full))
//             return ;
//     }

// }
