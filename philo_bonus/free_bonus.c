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

#include "philo_bonus.h"

void free_data(t_data *data)
{
	int i;

	i = -1;
	if (!data)
		return ;
	pthread_mutex_destroy(&(data->checkin_death_m));
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
