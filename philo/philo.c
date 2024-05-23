/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/22 13:38:45 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_data *data, int id)
{
	// pthread_mutex_lock(&(data->mutex));
	if (id == (data->number_of_philosophers - 1))
	{
		// printf("philo num = %d\n", data->philo_num);
		// pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_lock(&(data->mutex_array[id]));
		// printf("fork id = %d  --  %d was taken it\n", id, data->forks[id]);
		data->forks[id] = -1;
		pthread_mutex_unlock(&(data->mutex_array[id]));
		pthread_mutex_lock(&(data->mutex_array[0]));
		// printf("fork id = %d  --  %d was taken it\n", 0, data->forks[0]);
		data->forks[0] = -1;
		pthread_mutex_unlock(&(data->mutex_array[0]));
	}
	else
	{
		// pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_lock(&(data->mutex_array[id]));
		// printf("fork id = %d  --  %d was taken it\n", id, data->forks[id]);
		data->forks[id] = -1;
		pthread_mutex_unlock(&(data->mutex_array[id]));
		pthread_mutex_lock(&(data->mutex_array[id + 1]));
		// printf("fork id = %d  --  %d was taken it\n", id + 1, data->forks[id + 1]);
		data->forks[id + 1] = -1;
		pthread_mutex_unlock(&(data->mutex_array[id + 1]));
	}
}

bool	check_forks(t_data *data, int id)
{
	// printf("id: %d\n", id);
	// printf("philo_num: %d\n", data->philo_num);
	// pthread_mutex_lock(&(data->mutex));
	if (id == (data->number_of_philosophers - 1))
	{
		// pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_lock(&(data->mutex_array[id]));
		if (data->forks[id] == -1)
		{
			// printf("id: %d\n", id);
			pthread_mutex_lock(&(data->mutex_array[0]));
			if (data->forks[0] == -1)
			{
				data->forks[0] = id;
				data->forks[id] = id;
				pthread_mutex_unlock(&(data->mutex_array[id]));
				pthread_mutex_unlock(&(data->mutex_array[0]));
				return (true);
			}
			pthread_mutex_unlock(&(data->mutex_array[0]));
		}
		pthread_mutex_unlock(&(data->mutex_array[id]));
	}
	else
	{
		// pthread_mutex_unlock(&(data->mutex));
		pthread_mutex_lock(&(data->mutex_array[id]));
		if (data->forks[id] == -1)
		{
			pthread_mutex_lock(&(data->mutex_array[id + 1]));
			if (data->forks[id + 1] == -1)
			{
				data->forks[id + 1] = id;
				data->forks[id] = id;
				pthread_mutex_unlock(&(data->mutex_array[id + 1]));
				pthread_mutex_unlock(&(data->mutex_array[id]));
				return (true);
			}
			pthread_mutex_unlock(&(data->mutex_array[id + 1]));
		}
		pthread_mutex_unlock(&(data->mutex_array[id]));
	}
	return (false);
}

void	ft_exit(t_philo **philo_array)
{
	int i;

	if (philo_array[0]->data->philo_died)
	{
		i = philo_array[0]->data->philo_died - 1;
		ft_putstr_fd("\033[9;3;31m", 2);
		ft_putnbr_fd(get_time_cal(&philo_array[i]->curr_time, &philo_array[i]->start_time), 2);
		ft_putstr_fd(" ", 2);
		ft_putnbr_fd(philo_array[0]->data->philo_died, 2);
		ft_putstr_fd(" died\033[0m\n", 2);
		free_philo_array(philo_array);
		exit(EXIT_FAILURE);
	}
	else
	{
		free_philo_array(philo_array);
		exit(EXIT_SUCCESS);
	}
}

bool check_death(t_data *data)
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
			free_data(data);
			exit(EXIT_FAILURE);
		}
		philo_array = init_phils_array(data, av);
		if (!philo_array)
			return (1);
		while (++i < data->number_of_philosophers)
		{
			pthread_create(&(philo_array[i]->thread),
				NULL, routin, philo_array[i]);
		}
		i = -1;
		while (++i < data->number_of_philosophers)
			pthread_join(philo_array[i]->thread, NULL);
		ft_exit(philo_array);
	}
	return (0);
}
