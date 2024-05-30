/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:12:20 by aken              #+#    #+#             */
/*   Updated: 2024/05/30 08:29:31 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	if (!data)
		return ;
	pthread_mutex_destroy(&(data->checkin_death_m));
	pthread_mutex_destroy(&(data->m_print));
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&(data->mutex_array[i]));
	if (data->mutex_array)
		free(data->mutex_array);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
}

int	free_philo_array(t_philo **philo_array)
{
	int		i;

	i = -1;
	if (philo_array == NULL || philo_array[0] == NULL)
		return (1);
	free_data(philo_array[0]->data);
	while (philo_array[++i])
		free(philo_array[i]);
	free(philo_array);
	return (1);
}

void	ft_exit(t_philo **philo_array)
{
	int	i;

	if (philo_array[0]->data->philo_died)
	{
		i = philo_array[0]->data->philo_died - 1;
		gettimeofday(&(philo_array[i]->curr_time), NULL);
		printf("\033[9;3;2;31m%ld %d died\033[0m\n",
			get_time_cal(philo_array[i]->curr_time,
				philo_array[i]->start_time), philo_array[0]->data->philo_died);
		free_philo_array(philo_array);
		exit(1);
	}
	else
	{
		free_philo_array(philo_array);
		exit(0);
	}
}
