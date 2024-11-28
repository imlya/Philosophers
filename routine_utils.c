#include "philo.h"

int	ft_solo_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->nb_philo == 1)
	{
		ft_print(philo, "has taken a fork\n");
		pthread_mutex_unlock(&philo->data->data_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (0);
}
