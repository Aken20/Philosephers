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

int	philo_free(t_philo	***philo)
{
	int		i;
	t_philo	**p;

	if (philo == NULL)
		return (1);
	p = *philo;
	i = -1;
	if (!p || !*p)
		return (1);
	// while ((p[0])->my_struct->mutex_array[++i])
	// 	free((p[0])->my_struct->mutex_array[i]);
	// if (p->my_struct->forks)
	// 	free(p->my_struct->forks);
	// if (p->my_struct)
	// 	free(p->my_struct);
	// i = -1;
	while (p[++i])
		free(p[i]);
	if (p)
		free(p);
	return (1);
}
// {
// 	int	i;

// 	i = -1;
// 	if (!my_struct || !*my_struct)
// 		return (1);
// 	while (i++ < (*my_struct)->philo_num)
// 		free((*my_struct)->philos[i]);
// 	if ((*my_struct) && (*my_struct)->philos)
// 		free((*my_struct)->philos);
// 	if ((*my_struct) && (*my_struct)->mutex_array)
// 		free((*my_struct)->mutex_array);
// 	if ((*my_struct))
// 		free((*my_struct));
// 	return (1);
// }

t_philo	*init_philo(char **av)
{
	t_philo	*philo;

	philo = calloc(sizeof(t_philo), 1);
	if (!philo)
		return (printf("Error: malloc failed\n"), NULL);
	if (ft_atoi(av[1]) == 90000000000
		|| ft_atoi(av[2]) == 90000000000
		|| ft_atoi(av[3]) == 90000000000 || ft_atoi(av[3]) < 60
		|| ft_atoi(av[4]) == 90000000000 || ft_atoi(av[4]) < 60
		|| ft_atoi(av[1]) <= 0)
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
	philo->time_to_think = 0;
	return (philo);
}



t_my_struct	*init_threads(int num_of_threads)
{
	t_my_struct	*thread;
	int			i;

	i = -1;
	thread = calloc(sizeof(t_my_struct), 1);
	if (!thread)
		return (printf("Error: malloc failed\n"), NULL);
	thread->forks = calloc(sizeof(int *), (num_of_threads + 1));
	thread->philo_num = num_of_threads;
	thread->mutex_array = calloc(sizeof(pthread_mutex_t), num_of_threads);
	if (!thread->forks || !thread->mutex_array)
		return (printf("Error: malloc failed\n"), NULL);
	while (++i < num_of_threads)
		pthread_mutex_init(&(thread->mutex_array[i]), NULL);
	i = -1;
	while (++i < num_of_threads)
		thread->forks[i] = -1;
	pthread_mutex_init(&(thread->mutex), NULL);
	pthread_mutex_init(&(thread->mutex_2), NULL);
	thread->philo_died = false;
	gettimeofday((&thread->start_time), NULL);
	return (thread);
}

t_philo	**init_phils_array(int num_of_philo, char **av)
{
	int			i;
	t_philo		**philos;
	t_my_struct	*my_struct;

	i = -1;
	philos = calloc(sizeof(t_philo *), num_of_philo + 1);
	my_struct = init_threads(num_of_philo);
	if (!philos)
		return (printf("Error: malloc failed\n"), NULL);
	philos[num_of_philo] = NULL;
	while (++i < num_of_philo)
	{
		philos[i] = init_philo(av);
		philos[i]->my_struct = my_struct;
		if (!philos[i])
			return (philo_free(&(philos)), NULL);
		philos[i]->pilo_num = i + 1;
		// printf("a philo_num: %d\n", philos[i]->pilo_num);
		// philos[i]->my_struct->forks[i] = -1;
		// pthread_mutex_init(&(my_struct->mutex_array[i]), NULL);
	}
	return (philos);
}
