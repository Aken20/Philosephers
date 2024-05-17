/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/17 19:07:31 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long	get_time_cal(struct timeval *curr_time, struct timeval *start_time)
{
	return (((curr_time->tv_sec - start_time->tv_sec) * 1000
			+ ((curr_time->tv_usec - start_time->tv_usec) / 1000)));
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
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->pilo_num);
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;32m%ld :%d philo %d is eating\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->num_of_meals, philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_usleep(philo->time_to_eat);
			gettimeofday((&philo->eat_time), NULL);
			philo->number_of_times--;
			pthread_mutex_lock(&(my_struct->forks_mutex));
			my_struct->forks += 2;
			pthread_mutex_unlock(&(my_struct->forks_mutex));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;30m%ld :%d philo %d is sleeping\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->num_of_meals++, philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_usleep(philo->time_to_sleep);
		}
		else
		{
			pthread_mutex_unlock(&(my_struct->mutex_2));
			gettimeofday(&(philo->die_time), NULL);
			if (get_time_cal(&philo->die_time, &philo->eat_time)
				> philo->time_to_die / 1000)
			{
				printf("\033[9;3;31m%ld :philo %d is died\033[0m\n",
					get_time_cal(&my_struct->curr_time, &my_struct->start_time),
					philo->pilo_num);
				philo_free(&my_struct);
				exit (1);
			}
		}
		pthread_mutex_unlock(&(my_struct->forks_mutex));
	}
	return (NULL);
}

void	ft_exit(t_my_struct *my_struct)
{
	pthread_mutex_destroy(&(my_struct->mutex));
	pthread_mutex_destroy(&(my_struct->mutex_2));
	pthread_mutex_destroy(&(my_struct->forks_mutex));
	philo_free(&my_struct);
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
		if (!my_struct)
			return (1);
		my_struct->forks = ft_atoi(av[1]);
		while (++i < num_of_philo)
		{
			pthread_mutex_lock(&(my_struct->mutex_2));
			my_struct->philo_num = i;
			pthread_create(&my_struct->philos[i]->thread,
				NULL, ft_philo, my_struct);
		}
		i = -1;
		while (++i < num_of_philo)
			pthread_join(my_struct->philos[i]->thread, NULL);
		ft_exit(my_struct);
	}
	return (0);
}
