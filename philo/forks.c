/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 13:17:50 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/05/30 06:43:52 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_data *data, int id)
{
	if (id == (data->number_of_philosophers - 1))
	{
		pthread_mutex_unlock(&(data->mutex_array[id]));
		pthread_mutex_unlock(&(data->mutex_array[0]));
	}
	else
	{
		pthread_mutex_unlock(&(data->mutex_array[id]));
		pthread_mutex_unlock(&(data->mutex_array[id + 1]));
	}
}

bool	chech_for_last_philo(t_data *data, int id)
{
	pthread_mutex_lock(&(data->mutex_array[id]));
	if (data->forks[id] != id)
	{
		pthread_mutex_lock(&(data->mutex_array[0]));
		if (data->forks[0] != id)
		{
			data->forks[0] = id;
			data->forks[id] = id;
			return (true);
		}
		pthread_mutex_unlock(&(data->mutex_array[0]));
	}
	pthread_mutex_unlock(&(data->mutex_array[id]));
	return (false);
}

bool	chech_for_last_philo_odd(t_data *data, int id, t_philo *philo)
{
	if (data->number_of_philosophers == 1)
		return (single_philo(philo));
	pthread_mutex_lock(&(data->mutex_array[0]));
	if (data->forks[0] != id)
	{
		pthread_mutex_lock(&(data->mutex_array[id]));
		if (data->forks[id] != id)
		{
			data->forks[0] = id;
			data->forks[id] = id;
			return (true);
		}
		pthread_mutex_unlock(&(data->mutex_array[id]));
	}
	pthread_mutex_unlock(&(data->mutex_array[0]));
	return (false);
}

bool	check_forks_odd(t_data *data, int id, t_philo *philo)
{
	if (id == (data->number_of_philosophers - 1))
		return (chech_for_last_philo_odd(data, id, philo));
	else
	{
		pthread_mutex_lock(&(data->mutex_array[id + 1]));
		if (data->forks[id + 1] != id)
		{
			pthread_mutex_lock(&(data->mutex_array[id]));
			if (data->forks[id] != id)
			{
				data->forks[id + 1] = id;
				data->forks[id] = id;
				return (true);
			}
			pthread_mutex_unlock(&(data->mutex_array[id]));
		}
		pthread_mutex_unlock(&(data->mutex_array[id + 1]));
	}
	return (false);
}

bool	check_forks(t_data *data, int id, t_philo *philo)
{
	if ((id % 2) == 0)
		return (check_forks_odd(data, id, philo));
	if (id == (data->number_of_philosophers - 1))
		return (chech_for_last_philo(data, id));
	else
	{
		pthread_mutex_lock(&(data->mutex_array[id]));
		if (data->forks[id] != id)
		{
			pthread_mutex_lock(&(data->mutex_array[id + 1]));
			if (data->forks[id + 1] != id)
			{
				data->forks[id + 1] = id;
				data->forks[id] = id;
				return (true);
			}
			pthread_mutex_unlock(&(data->mutex_array[id + 1]));
		}
		pthread_mutex_unlock(&(data->mutex_array[id]));
	}
	return (false);
}
