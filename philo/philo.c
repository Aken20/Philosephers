/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/11 16:36:34 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(int desired_sleep_us)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, 0);
	while ((end_time.tv_usec - start_time.tv_usec) < desired_sleep_us)
		gettimeofday(&end_time, 0);
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
	if (ft_atoi(av[1]) == 90000000000
		|| ft_atoi(av[2]) == 90000000000
		|| ft_atoi(av[3]) == 90000000000
		|| ft_atoi(av[4]) == 90000000000)
		exit (1);
	if (av[2])
		philo->time_to_die = ft_atoi(av[2]);
	if (av[3])
		philo->time_to_eat = ft_atoi(av[3]);
	if (av[4])
		philo->time_to_sleep = ft_atoi(av[4]);
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
	thread->philos = calloc(sizeof(t_philo *), num_of_threads + 1);
	pthread_mutex_init(&(thread->mutex), NULL);
	pthread_mutex_init(&(thread->mutex_2), NULL);
	pthread_mutex_init(&(thread->forks_mutex), NULL);
	thread->philos[num_of_threads] = NULL;
	thread->philo_died = false;
	while (++i < num_of_threads)
	{
		thread->philos[i] = init_philo(av);
		thread->philos[i]->pilo_num = i + 1;
	}
	return (thread);
}

void	*ft_philo(void *p)
{
	t_my_struct	*my_struct;
	t_philo		*philo;
	int			philo_num;
	int			i;

	i = 0;
	my_struct = (t_my_struct *)p;
	philo_num = my_struct->philo_num;
	pthread_mutex_unlock(&(my_struct->mutex_2));
	philo = my_struct->philos[philo_num];
	// philo->die_time = malloc(sizeof())
	while (philo->number_of_times)
	{
		pthread_mutex_lock(&(my_struct->mutex));
		gettimeofday((&my_struct->curr_time), NULL);
		gettimeofday((&philo->eat_time), NULL);
		pthread_mutex_unlock(&(my_struct->mutex));
		pthread_mutex_lock(&(my_struct->forks_mutex));
		if (my_struct->forks >= 2)
		{
			printf("\e[1;33m%d :philo %d has picked up 2 forks\e[0m\n", (my_struct->curr_time.tv_usec - my_struct->start_time.tv_usec), philo->pilo_num);
			my_struct->forks -= 2;
			// pthread_mutex_lock(&(my_struct->mutex));
			// gettimeofday((&my_struct->curr_time), NULL);
			printf("\e[1;32m%d :%d philo %d is eating\e[0m\n", (my_struct->curr_time.tv_usec - my_struct->start_time.tv_usec), i + 1, philo->pilo_num);
			// pthread_mutex_unlock(&(my_struct->mutex));
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			my_usleep(philo->time_to_eat);
			philo->number_of_times--;
			// pthread_mutex_lock(&(my_struct->forks_mutex));
			// pthread_mutex_lock(&(my_struct->mutex));
			// gettimeofday((&my_struct->curr_time), NULL);
			// pthread_mutex_unlock(&(my_struct->mutex));
			printf("\e[1;33m%d :philo %d has droped 2 forks\e[0m\n", (my_struct->curr_time.tv_usec - my_struct->start_time.tv_usec), philo->pilo_num);
			pthread_mutex_lock(&(my_struct->forks_mutex));
			my_struct->forks += 2;
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			// printf("%d :%d philo %d is sleeping\n", (my_struct->curr_time.tv_usec - my_struct->start_time.tv_usec), i++ + 1, philo->pilo_num);
			// pthread_mutex_lock(&(my_struct->mutex_2));
			// my_usleep(philo->time_to_sleep);
			// pthread_mutex_unlock(&(my_struct->mutex_2));
			// pthread_mutex_unlock(&(my_struct->forks_mutex));
		}
		else
		{
			// pthread_mutex_lock(&(my_struct->forks_mutex));
			// pthread_mutex_lock(&(my_struct->mutex));
			gettimeofday(&(philo->die_time), NULL);
			// printf("%d   %d\n", (philo->die_time.tv_usec - my_struct->start_time.tv_usec),  (philo->eat_time.tv_usec - my_struct->start_time.tv_usec));
			// pthread_mutex_unlock(&(my_struct->mutex));
			// if (my_struct->forks >= 2)
			// {
			// 	continue;
			// }
			if ((philo->die_time.tv_usec - philo->eat_time.tv_usec) > philo->time_to_die)
			{
				// pthread_mutex_lock(&(my_struct->mutex));
				// if (my_struct->philo_died == true)
				// 	return (pthread_mutex_unlock(&(my_struct->mutex)), NULL);
				// pthread_mutex_unlock(&(my_struct->mutex));
				// my_struct->philo_died = true;
				// pthread_mutex_lock(&(my_struct->mutex));
				// gettimeofday((&my_struct->curr_time), NULL);
				// pthread_mutex_unlock(&(my_struct->mutex));
				printf("\033[9;3;31m%d :philo %d is died\033[0m\n", (my_struct->start_time.tv_usec - my_struct->start_time.tv_usec), philo->pilo_num);
				philo_free(&my_struct);
				exit (1);
			}
		}
		pthread_mutex_unlock(&(my_struct->forks_mutex));
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_my_struct	*my_struct;
	int			i;
	int			num_of_philo;

	if (ac == 5 || ac == 6)
	{
		i = -1;
		num_of_philo = ft_atoi(av[1]);
		my_struct = init_threads(num_of_philo, av);
		gettimeofday((&my_struct->start_time), NULL);
		my_struct->forks = ft_atoi(av[1]);
		while (++i < num_of_philo)
		{
			pthread_mutex_lock(&(my_struct->mutex_2));
			my_struct->philo_num = i;
			pthread_create(&my_struct->philos[i]->thread, NULL, ft_philo, my_struct);
		}
		i = -1;
		while (++i < num_of_philo)
			pthread_join(my_struct->philos[i]->thread, NULL);
		i = -1;
		pthread_mutex_destroy(&(my_struct->mutex));
		pthread_mutex_destroy(&(my_struct->mutex_2));
		pthread_mutex_destroy(&(my_struct->forks_mutex));
		philo_free(&my_struct);
	}
	return (0);
}
