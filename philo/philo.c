/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/14 21:39:21 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long desired_sleep_us)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, 0);
	gettimeofday(&end_time, 0);
	while ((((end_time.tv_sec - start_time.tv_sec) * 1000 + (end_time.tv_usec / 1000)) - (start_time.tv_usec / 1000)) < desired_sleep_us / 1000)
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
	if (ft_atoi(av[1]) == 90000000000
		|| ft_atoi(av[2]) == 90000000000
		|| ft_atoi(av[3]) == 90000000000 || ft_atoi(av[3]) <= 60
		|| ft_atoi(av[4]) == 90000000000 || ft_atoi(av[4]) <= 60)
		exit (printf("Error: invalid arguments\n"));
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

int	get_phlilo_turn(t_my_struct *my_struct)
{
	int	j;

	j = 0;
	while (my_struct->philos[j])
	{
		if (my_struct->philos[j + 1]
			&& my_struct->philos[j]->num_of_meals
			>= my_struct->philos[j + 1]->num_of_meals)
			j++;
		else
			return (j);
	}
	return (j);
}

void	*ft_philo(void *p)
{
	t_my_struct	*my_struct;
	t_philo		*philo;
	int			philo_num;

	my_struct = (t_my_struct *)p;
	philo_num = my_struct->philo_num;
	pthread_mutex_unlock(&(my_struct->mutex_2));
	philo = my_struct->philos[philo_num];
	philo->num_of_meals = 1;
	pthread_mutex_lock(&(my_struct->mutex));
	gettimeofday((&my_struct->curr_time), NULL);
	gettimeofday((&philo->eat_time), NULL);
	pthread_mutex_unlock(&(my_struct->mutex));
	while (philo->number_of_times)
	{
		pthread_mutex_lock(&(my_struct->mutex));
		gettimeofday((&my_struct->curr_time), NULL);
		pthread_mutex_unlock(&(my_struct->mutex));
		pthread_mutex_lock(&(my_struct->forks_mutex));
		pthread_mutex_lock(&(my_struct->mutex_2));
		if (my_struct->forks >= 2 && philo_num == get_phlilo_turn(my_struct))
		{
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_struct->forks -= 2;
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n", (((my_struct->curr_time.tv_sec - my_struct->start_time.tv_sec) * 1000 + (my_struct->curr_time.tv_usec / 1000)) - (my_struct->start_time.tv_usec / 1000)), philo->pilo_num);
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n", (((my_struct->curr_time.tv_sec - my_struct->start_time.tv_sec) * 1000 + (my_struct->curr_time.tv_usec / 1000)) - (my_struct->start_time.tv_usec / 1000)), philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;32m%ld :%d philo %d is eating\e[0m\n", (((my_struct->curr_time.tv_sec - my_struct->start_time.tv_sec) * 1000 + (my_struct->curr_time.tv_usec / 1000)) - (my_struct->start_time.tv_usec / 1000)), philo->num_of_meals, philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_usleep(philo->time_to_eat);
			gettimeofday((&philo->eat_time), NULL);
			philo->number_of_times--;
			pthread_mutex_lock(&(my_struct->forks_mutex));
			my_struct->forks += 2;
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;30m%ld :%d philo %d is sleeping\e[0m\n", (((my_struct->curr_time.tv_sec - my_struct->start_time.tv_sec) * 1000 + (my_struct->curr_time.tv_usec / 1000)) - (my_struct->start_time.tv_usec / 1000)), philo->num_of_meals++, philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_usleep(philo->time_to_sleep);
		}
		else
		{
			gettimeofday(&(philo->die_time), NULL);
			if ((((philo->die_time.tv_sec - philo->eat_time.tv_sec) * 1000 + (philo->die_time.tv_usec / 1000)) - (philo->eat_time.tv_usec / 1000)) > philo->time_to_die / 1000)
			{
				printf("\033[9;3;31m%ld :philo %d is died\033[0m\n", (((my_struct->curr_time.tv_sec - my_struct->start_time.tv_sec) * 1000 + (my_struct->curr_time.tv_usec / 1000)) - (my_struct->start_time.tv_usec / 1000)), philo->pilo_num);
				philo_free(&my_struct);
				exit (1);
			}
		}
		pthread_mutex_unlock(&(my_struct->mutex_2));
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
