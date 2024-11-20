/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imatek <imatek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:15:36 by imatek            #+#    #+#             */
/*   Updated: 2024/11/20 14:55:54 by imatek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * sign);
}

int	ft_check_digit(char *av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (av[i] < '0' || av[i] > '9')
			return (-1);
		i++;
	}
	return (1);
}

int	ft_parse(char **av)
{
	if (ft_atol(av[1]) <= 0 || ft_atol(av[1]) > 200)
		return (0);
	if (ft_atol(av[2]) < 60 || ft_atol(av[3]) < 60 || ft_atol(av[4]) < 60)
		return (0);
	return (1);
}
