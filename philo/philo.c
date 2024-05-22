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

// int	get_phlilo_turn(t_my_struct *my_struct)
// {
// 	int	j;

// 	j = 0;
// 	while (my_struct->philos[j])
// 	{
// 		if (my_struct->philos[j + 1]
// 			&& my_struct->philos[j]->num_of_meals
// 			>= my_struct->philos[j + 1]->num_of_meals)
// 			j++;
// 		else
// 			return (j);
// 	}
// 	return (j);
// }

long	get_time_cal(struct timeval *curr_time, struct timeval *start_time)
{
	return (((curr_time->tv_sec - start_time->tv_sec) * 1000
			+ ((curr_time->tv_usec - start_time->tv_usec) / 1000)));
}

void	unlock_forks(t_my_struct *my_struct, int id)
{
	// printf("shosort\n");
	if (id == (my_struct->philo_num - 1))
	{
		// pthread_mutex_lock(&(my_struct->mutex_array[0]));
		my_struct->forks[0] = -1;
		pthread_mutex_unlock(&(my_struct->mutex_array[0]));
		// pthread_mutex_lock(&(my_struct->mutex_array[id]));
		my_struct->forks[id] = -1;
		pthread_mutex_unlock(&(my_struct->mutex_array[id]));
	}
	else
	{
		// pthread_mutex_lock(&(my_struct->mutex_array[id - 1]));
		my_struct->forks[id + 1] = -1;
		pthread_mutex_unlock(&(my_struct->mutex_array[id - 1]));
		// pthread_mutex_lock(&(my_struct->mutex_array[id]));
		my_struct->forks[id] = -1;
		pthread_mutex_unlock(&(my_struct->mutex_array[id]));
	}
}

bool	check_forks(t_my_struct *my_struct, int id)
{
	// printf("id: %d\n", id);
	// printf("philo_num: %d\n", my_struct->philo_num);
	if (id == my_struct->philo_num - 1)
	{
		pthread_mutex_lock(&(my_struct->mutex_array[id]));
		if (my_struct->forks[id] == -1)
		{
			// printf("id: %d\n", id);
			pthread_mutex_lock(&(my_struct->mutex_array[0]));
			if (my_struct->forks[0] == -1)
			{
				my_struct->forks[0] = id;
				my_struct->forks[id] = id;
				// pthread_mutex_unlock(&(my_struct->mutex_array[id]));
				// pthread_mutex_unlock(&(my_struct->mutex_array[0]));
				return (true);
			}
			pthread_mutex_unlock(&(my_struct->mutex_array[0]));
		}
		else
			pthread_mutex_unlock(&(my_struct->mutex_array[id]));
	}
	else
	{
		pthread_mutex_lock(&(my_struct->mutex_array[id]));
		if (my_struct->forks[id] == -1)
		{
			pthread_mutex_lock(&(my_struct->mutex_array[id + 1]));
			if (my_struct->forks[id + 1] == -1)
			{
				my_struct->forks[id + 1] = id;
				my_struct->forks[id] = id;
				// pthread_mutex_unlock(&(my_struct->mutex_array[id + 1]));
				// pthread_mutex_unlock(&(my_struct->mutex_array[id]));
				return (true);
			}
			pthread_mutex_unlock(&(my_struct->mutex_array[id + 1]));
		}
		else
			pthread_mutex_unlock(&(my_struct->mutex_array[id]));
	}
	return (false);
}

void	ft_exit(t_philo **philos)
{
	pthread_mutex_destroy(&(philos[0]->my_struct->mutex));
	pthread_mutex_destroy(&(philos[0]->my_struct->mutex_2));
	philo_free(&philos);
	exit(0);
}

void	*ft_philo(void *p)
{
	t_my_struct	*my_struct;
	t_philo		*philo;

	philo = (t_philo *)p;
	my_struct = philo->my_struct;
	philo->num_of_meals = 1;
	pthread_mutex_lock(&(my_struct->mutex));
	// printf("philo_num: %d\n", philo->pilo_num);
	gettimeofday((&my_struct->curr_time), NULL);
	gettimeofday((&philo->eat_time), NULL);
	pthread_mutex_unlock(&(my_struct->mutex));
	if (philo->pilo_num % 2 == 0)
		my_usleep(10);
	while (philo->number_of_times)
	{
		pthread_mutex_lock(&(my_struct->mutex));
		gettimeofday((&my_struct->curr_time), NULL);
		pthread_mutex_unlock(&(my_struct->mutex));
		pthread_mutex_lock(&(my_struct->mutex_2));
		if (check_forks(my_struct, philo->pilo_num - 1) == true)
		{
			// pthread_mutex_unlock(&(my_struct->mutex_2));
			// pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			pthread_mutex_lock(&(my_struct->mutex_2));
			printf("\e[1;32m%ld :%d philo %d is eating\e[0m\n",
				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
				philo->num_of_meals, philo->pilo_num);
			pthread_mutex_unlock(&(my_struct->mutex_2));
			my_usleep(philo->time_to_eat);
			unlock_forks(my_struct, philo->pilo_num - 1);
			pthread_mutex_lock(&(my_struct->mutex_2));
			gettimeofday((&philo->eat_time), NULL);
			philo->number_of_times--;
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
				pthread_mutex_lock(&(my_struct->mutex));
				printf("\033[9;3;31m%ld :philo %d has died\033[0m\n",
					get_time_cal(&my_struct->curr_time, &my_struct->start_time),
					philo->pilo_num);
				ft_exit(&philo);
			}
		}
	}
	return (NULL);
}

// void	*ft_philo(void *p)
// {
// 	t_my_struct	*my_struct;
// 	t_philo		*philo;
// 	int			philo_num;

// 	my_struct = (t_my_struct *)p;
// 	philo_num = my_struct->philo_num;
// 	pthread_mutex_unlock(&(my_struct->mutex_2));
// 	philo = my_struct->philos[philo_num];
// 	philo->num_of_meals = 1;
// 	pthread_mutex_lock(&(my_struct->mutex));
// 	gettimeofday((&my_struct->curr_time), NULL);
// 	gettimeofday((&philo->eat_time), NULL);
// 	pthread_mutex_unlock(&(my_struct->mutex));
// 	while (philo->number_of_times)
// 	{
// 		pthread_mutex_lock(&(my_struct->mutex));
// 		gettimeofday((&my_struct->curr_time), NULL);
// 		pthread_mutex_unlock(&(my_struct->mutex));
// 		pthread_mutex_lock(&(my_struct->forks_mutex));
// 		pthread_mutex_lock(&(my_struct->mutex_2));
// 		if (my_struct->forks >= 2)
// 		{
// 			pthread_mutex_unlock(&(my_struct->mutex_2));
// 			my_struct->forks -= 2;
// 			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
// 				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
// 				philo->pilo_num);
// 			printf("\e[1;33m%ld :philo %d has taken a fork\e[0m\n",
// 				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
// 				philo->pilo_num);
// 			pthread_mutex_unlock(&(my_struct->forks_mutex));
// 			pthread_mutex_lock(&(my_struct->mutex_2));
// 			printf("\e[1;32m%ld :%d philo %d is eating\e[0m\n",
// 				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
// 				philo->num_of_meals, philo->pilo_num);
// 			pthread_mutex_unlock(&(my_struct->mutex_2));
// 			my_usleep(philo->time_to_eat);
// 			gettimeofday((&philo->eat_time), NULL);
// 			philo->number_of_times--;
// 			pthread_mutex_lock(&(my_struct->forks_mutex));
// 			my_struct->forks += 2;
// 			pthread_mutex_unlock(&(my_struct->forks_mutex));
// 			pthread_mutex_lock(&(my_struct->mutex_2));
// 			printf("\e[1;30m%ld :%d philo %d is sleeping\e[0m\n",
// 				get_time_cal(&my_struct->curr_time, &my_struct->start_time),
// 				philo->num_of_meals++, philo->pilo_num);
// 			pthread_mutex_unlock(&(my_struct->mutex_2));
// 			my_usleep(philo->time_to_sleep);
// 		}
// 		else
// 		{
// 			pthread_mutex_unlock(&(my_struct->mutex_2));
// 			gettimeofday(&(philo->die_time), NULL);
// 			if (get_time_cal(&philo->die_time, &philo->eat_time)
// 				> philo->time_to_die / 1000)
// 			{
// 				printf("\033[9;3;31m%ld :philo %d is died\033[0m\n",
// 					get_time_cal(&my_struct->curr_time, &my_struct->start_time),
// 					philo->pilo_num);
// 				philo_free(&my_struct);
// 				exit (1);
// 			}
// 		}
// 		pthread_mutex_unlock(&(my_struct->forks_mutex));
// 	}
// 	return (NULL);
// }

int	main(int ac, char **av)
{
	t_philo		**philos;
	int			i;
	int			num_of_philo;

	if (ac == 5 || ac == 6)
	{
		i = -1;
		num_of_philo = ft_atoi(av[1]);
		philos = NULL;
		philos = init_phils_array(num_of_philo, av);
		if (!philos)
			return (1);
		while (++i < num_of_philo)
		{
			// philos[i]->pilo_num = i + 1;
			// printf("philo_num: %d\n", philos[i]->pilo_num);
			// pthread_mutex_lock(&(my_struct->mutex_2));
			pthread_create(&(philos[i]->thread),
				NULL, ft_philo, philos[i]);
		}
		i = -1;
		while (++i < num_of_philo)
			pthread_join(philos[i]->thread, NULL);
		ft_exit(philos);
	}
	return (0);
}
