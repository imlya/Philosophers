/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Moon <Moon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:02:24 by imatek            #+#    #+#             */
/*   Updated: 2024/11/28 03:26:38 by Moon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_destroy_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork_mutex[i]);
	}
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->philo->last_meal_mutex);
	free(data->fork_mutex);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL, printf("malloc data error\n"), -1);
	memset(data, 0, sizeof(t_data));
	if (ac < 5 || ac > 6)
		return (free(data), printf("Error : Too many/few args\n"), -1);
	if (!ft_parse(av) || !ft_check_digit(*av))
		return (free(data), printf("parse error\n"), -1);
	if (!ft_init_data(data, ac, av) || !ft_init_philo(data, av))
		return (free(data), printf("init error\n"), -1);
	ft_thread(data);
	ft_destroy_mutex(data);
	free(data->philo);
	free(data);
	return (0);
}
