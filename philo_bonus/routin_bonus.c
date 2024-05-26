/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:34:00 by aken              #+#    #+#             */
/*   Updated: 2024/05/26 19:06:23 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	taking_forks(t_philo *philo)
{
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
}

bool	sleeping(t_philo *philo)
{
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is sleeping\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	if (my_usleep(philo->time_to_sleep, philo) == false)
		return (false);
	return (true);
}

void	thinking(t_philo *philo)
{
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is thinking\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
}

bool	eating(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	printf("\e[1;32m%ld %d is eating\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	gettimeofday((&philo->eat_time), NULL);
	if (my_usleep(philo->time_to_eat, philo) == false)
		return (false);
	// gettimeofday((&philo->curr_time), NULL);
	// printf("\e[1;32m%ld %d has ate %d\e[0m\n",
	// 	get_time_cal(&philo->curr_time, &philo->start_time),
	// 	philo->id, philo->num_of_meals++);
	unlock_forks(philo);
	philo->number_of_times--;
	return (true);
}

bool	routin(void *p)
{
	t_data		*data;
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
		if (check_forks(philo) == true)
		{
			taking_forks(philo);
			if (eating(philo) == false)
				return (false);
			if (sleeping(philo) == false)
				return (false);
			thinking(philo);
		}
		else
			if (set_dead(philo, philo->id) == false)
				return (false);
	}
	return (true);
}
