/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/26 14:16:07 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	single_philo(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	my_usleep(philo->time_to_die, philo);
	pthread_mutex_lock(&(philo->data->checkin_death_m));
	philo->data->philo_died = philo->id;
	pthread_mutex_unlock(&(philo->data->checkin_death_m));
	return (false);
}

bool	check_death(t_data *data)
{
	pthread_mutex_lock(&(data->checkin_death_m));
	if (data->philo_died != 0)
	{
		pthread_mutex_unlock(&(data->checkin_death_m));
		return (true);
	}
	pthread_mutex_unlock(&(data->checkin_death_m));
	return (false);
}

int	main(int ac, char **av)
{
	t_philo		**philo_array;
	t_data		*data;
	int			i;

	if (ac == 5 || ac == 6)
	{
		i = -1;
		data = init_data(av);
		if (data->number_of_philosophers > 200)
		{
			ft_putstr_fd("Do Not Enter More than 200", STDERR_FILENO);
			(free_data(data), exit(EXIT_FAILURE));
		}
		philo_array = init_philo_array(data, av);
		if (!philo_array)
			return (1);
		while (++i < data->number_of_philosophers)
			pthread_create(&(philo_array[i]->thread),
				NULL, routin, philo_array[i]);
		i = -1;
		while (++i < data->number_of_philosophers)
			pthread_join(philo_array[i]->thread, NULL);
		ft_exit(philo_array);
	}
	return (0);
}
