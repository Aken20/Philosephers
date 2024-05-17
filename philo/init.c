/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 05:04:23 by ahibrahi          #+#    #+#             */
/*   Updated: 2024/05/17 05:15:29 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long desired_sleep_us)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, 0);
	gettimeofday(&end_time, 0);
	while ((((end_time.tv_sec - start_time.tv_sec) * 1000
				+(end_time.tv_usec / 1000)) - (start_time.tv_usec / 1000))
		< desired_sleep_us / 1000)
	{
		usleep(500);
		gettimeofday(&end_time, 0);
	}
}

int	philo_free(t_my_struct	**my_struct)
{
	int	i;

	i = -1;
	if (!my_struct || !*my_struct)
		return (1);
	while (i++ < (*my_struct)->forks)
		free((*my_struct)->philos[i]);
	if ((*my_struct) && (*my_struct)->philos)
		free((*my_struct)->philos);
	if ((*my_struct))
		free((*my_struct));
	return (1);
}

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = calloc(sizeof(t_philo), 1);
	if (!philo)
		return (printf("Error: malloc failed\n"), NULL);
	if (ft_atoi(av[1]) == 90000000000
		|| ft_atoi(av[2]) == 90000000000
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
	philo->time_to_think = 0;
	return (philo);
}

t_my_struct	*init_threads(int num_of_threads, char **av)
{
	int			i;
	t_my_struct	*thread;

	i = -1;
	thread = calloc(sizeof(t_my_struct), 1);
	if (!thread)
		return (printf("Error: malloc failed\n"), NULL);
	thread->philos = calloc(sizeof(t_philo *), num_of_threads + 1);
	if (!thread->philos)
		return (printf("Error: malloc failed\n"), NULL);
	pthread_mutex_init(&(thread->mutex), NULL);
	pthread_mutex_init(&(thread->mutex_2), NULL);
	pthread_mutex_init(&(thread->forks_mutex), NULL);
	thread->philos[num_of_threads] = NULL;
	thread->philo_died = false;
	while (++i < num_of_threads)
	{
		thread->philos[i] = init_philo(av);
		if (!thread->philos[i])
			return (philo_free(&thread), NULL);
		thread->philos[i]->pilo_num = i + 1;
	}
	gettimeofday((&thread->start_time), NULL);
	return (thread);
}
