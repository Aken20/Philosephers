/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:04:23 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/05/22 13:32:15 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = calloc(sizeof(t_philo), 1);
	if (!philo)
		return (printf("Error: malloc failed\n"), NULL);
	if (ft_atoi(av[2]) == 90000000000
		|| ft_atoi(av[3]) == 90000000000 || ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) == 90000000000 || ft_atoi(av[4]) < 60)
		return (printf("Error: invalid arguments\n"), NULL);
	if (av[2])
		philo->time_to_die = (1000 * ft_atoi(av[2]));
	if (av[3])
		philo->time_to_eat = (1000 * ft_atoi(av[3]));
	if (av[4])
		philo->time_to_sleep = (1000 * ft_atoi(av[4]));
	if (av[5])
		philo->number_of_times = ft_atoi(av[5]);
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
	{
		printf("%s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	data = calloc(sizeof(t_data), 1);
	if (!data)
		return (printf("Error: malloc failed\n"), NULL);
	data->number_of_philosophers = ft_atoi(av[1]);
	data->forks = sem_open("forks", O_RDWR);
	data->pids = calloc(sizeof(int), (data->number_of_philosophers + 1));
	i = -1;
	while (++i < data->number_of_philosophers)
		data->forks[i] = -1;
	pthread_mutex_init(&(data->checkin_death_m), NULL);
	data->philo_died = 0;
	return (data);
}

t_philo	**init_philo_array(t_data *data, char **av)
{
	int			i;
	t_philo		**philo_array;

	i = -1;
	philo_array = calloc(sizeof(t_philo *), data->number_of_philosophers + 1);
	if (!philo_array)
		return (printf("Error: malloc failed\n"), NULL);
	philo_array[data->number_of_philosophers] = NULL;
	while (++i < data->number_of_philosophers)
	{
		philo_array[i] = init_philo(av);
		philo_array[i]->data = data;
		if (!philo_array[i])
			return (free_philo_array(philo_array), NULL);
		philo_array[i]->ID = i + 1;
	}
	return (philo_array);
}
