/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:04:23 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/05/30 08:09:23 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_philo *philo)
{
	gettimeofday(&(philo->curr_time), NULL);
	if (get_time_cal(philo->curr_time, philo->eat_time)
		>= (philo->time_to_die / 1000))
	{
		pthread_mutex_lock(&(philo->data->checkin_death_m));
		philo->data->philo_died = philo->id;
		pthread_mutex_unlock(&(philo->data->checkin_death_m));
	}
}

int	*alloc_forks(int num)
{
	int		*forks;

	forks = malloc(sizeof(int) * 2);
	if (!forks)
		return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
	forks[0] = -1;
	if (num % 2 != 0)
		forks[1] = num -1;
	else
		forks[1] = -1;
	return (forks);
}

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
	if (ft_atoi(av[2]) == 90000000000
		|| ft_atoi(av[3]) == 90000000000 || ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) == 90000000000 || ft_atoi(av[4]) < 60)
		return (ft_putstr_fd("Error: invalid arguments\n", 2), NULL);
	if (av[2])
		philo->time_to_die = (1000 * ft_atoi(av[2]));
	if (av[3])
		philo->time_to_eat = (1000 * ft_atoi(av[3]));
	if (av[4])
		philo->time_to_sleep = (1000 * ft_atoi(av[4]));
	if (av[5])
	{
		if (ft_atoi(av[5]) == 90000000000 || ft_atoi(av[5]) <= 0)
			return (ft_putstr_fd("Error: invalid arguments\n", 2), NULL);
		philo->number_of_times = ft_atoi(av[5]);
	}
	else
		philo->number_of_times = -1;
	philo->num_of_meals = 1;
	return (philo);
}

t_data	*init_data(char **av)
{
	t_data		*data;
	int			i;

	i = -1;
	if (ft_atoi(av[1]) == 90000000000 || ft_atoi(av[1]) <= 0)
		exit(1);
	data = malloc(sizeof(t_data));
	data->number_of_philosophers = ft_atoi(av[1]);
	data->forks = malloc(sizeof(int) * data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		if (i % 2 == 0)
			data->forks[i] = i - 1;
		else
			data->forks[i] = -1;
	}
	data->mutex_array = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_mutex_init(&(data->mutex_array[i]), NULL);
	pthread_mutex_init(&(data->checkin_death_m), NULL);
	pthread_mutex_init(&(data->m_print), NULL);
	data->philo_died = 0;
	return (data);
}

t_philo	**init_philo_array(t_data *data, char **av)
{
	int			i;
	t_philo		**philo_array;

	i = -1;
	philo_array = malloc(sizeof(t_philo *)
			* (data->number_of_philosophers + 1));
	if (!philo_array)
		return (ft_putstr_fd("Error: malloc failed\n", 2), NULL);
	while (++i < data->number_of_philosophers)
	{
		philo_array[i] = init_philo(av);
		if (!philo_array[i])
			return (free_philo_array(philo_array), NULL);
		philo_array[i]->data = data;
		philo_array[i]->id = i + 1;
	}
	philo_array[i] = NULL;
	return (philo_array);
}
