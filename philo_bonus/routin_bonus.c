/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-05-23 00:34:00 by aken              #+#    #+#             */
/*   Updated: 2024-05-23 00:34:00 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taking_forks(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->ID);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->ID);
}

void	sleeping(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is sleeping\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time)
		, philo->ID);
	my_usleep(philo->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is thinking\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time)
		, philo->ID);
}

void	eating(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;32m%ld %d is eating\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->ID);
	my_usleep(philo->time_to_eat);
	// gettimeofday((&philo->curr_time), NULL);
	// printf("\e[1;32m%ld %d has ate %d\e[0m\n",
	// 	get_time_cal(&philo->curr_time, &philo->start_time),
	// 	philo->ID, philo->num_of_meals++);
	unlock_forks(philo->data, philo->ID - 1);
	gettimeofday((&philo->eat_time), NULL);
	philo->number_of_times--;
}

void	*routin(void *p)
{
	t_data	*data;
	t_philo		*philo;

	philo = (t_philo *)p;
	data = philo->data;
	gettimeofday((&philo->start_time), NULL);
	gettimeofday((&philo->eat_time), NULL);
	while (philo->number_of_times)
	{
		gettimeofday(&(philo->curr_time), NULL);
		if (check_death(philo->data) == true)
			return (NULL);
		if (check_forks(data, philo->ID - 1) == true)
		{
			taking_forks(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		else
		{
			if (get_time_cal(&philo->curr_time, &philo->eat_time)
				> philo->time_to_die / 1000)
			{
				pthread_mutex_lock(&(philo->data->checkin_death_m));
				philo->data->philo_died = philo->ID;
				pthread_mutex_unlock(&(philo->data->checkin_death_m));
			}
		}
	}
	return (NULL);
}