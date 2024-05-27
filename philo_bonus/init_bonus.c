/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:04:23 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/05/26 18:59:10 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

bool	set_dead(t_philo *philo, int id)
{
	if (get_time_cal(&philo->curr_time, &philo->eat_time)
		> philo->time_to_die / 1000)
	{
		sem_wait(philo->data->checkin_death_m);
		philo->data->philo_died = id;
		printf("\e[1;31m%ld %d died\e[0m\n",
			get_time_cal(&philo->curr_time, &philo->start_time), id);
		exit (EXIT_FAILURE);
	}
	return (true);
}

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
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

	if (ft_atoi(av[1]) == 90000000000 || ft_atoi(av[1]) <= 0)
	{
		printf("%s\n", av[1]);
		exit(EXIT_FAILURE);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Error: malloc failed\n"), NULL);
	data->number_of_philosophers = ft_atoi(av[1]);
	sem_unlink("forks");
	sem_unlink("checkin_death_m");
	printf("number_of_philosophers: %d\n", data->number_of_philosophers);
	data->forks = sem_open("forks", O_CREAT, 0644, data->number_of_philosophers);
	if (data->forks == SEM_FAILED)
		perror("Error: sem_open failed\n");
	data->checkin_death_m = sem_open("checkin_death_m", O_CREAT, 0644, 1);
	if (data->checkin_death_m == SEM_FAILED)
		perror("Error: sem_open failed\n");
	data->pids = malloc(sizeof(int) * data->number_of_philosophers);
	data->philo_died = 0;
	return (data);
}

t_philo	**init_philo_array(t_data *data, char **av)
{
	int			i;
	t_philo		**philo_array;

	i = -1;
	philo_array = malloc(sizeof(t_philo *) * (data->number_of_philosophers + 1));
	if (!philo_array)
		return (printf("Error: malloc failed\n"), NULL);
	philo_array[data->number_of_philosophers] = NULL;
	while (++i < data->number_of_philosophers)
	{
		philo_array[i] = init_philo(av);
		philo_array[i]->data = data;
		if (!philo_array[i])
			return (free_philo_array(philo_array), NULL);
		philo_array[i]->id = i + 1;
	}
	return (philo_array);
}
