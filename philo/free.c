/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-23 01:12:20 by aken              #+#    #+#             */
/*   Updated: 2024-05-23 01:12:20 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void free_data(t_data *data)
{
	int i;

	i = -1;
	if (!data)
		return ;
	pthread_mutex_destroy(&(data->checkin_death_m));
	while (++i < data->number_of_philosophers)
		pthread_mutex_destroy(&(data->mutex_array[i]));
	if (data->mutex_array)
		free(data->mutex_array);
	if (data->forks)
		free(data->forks);
	if (data)
		free(data);
}

int	free_philo_array(t_philo	**philo_array)
{
	int		i;

	i = -1;
	if (philo_array == NULL)
		return (1);
	free_data(philo_array[0]->data);
	while (philo_array[++i])
		free(philo_array[i]);
	free(philo_array);
	return (1);
}
