/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:34:00 by aken              #+#    #+#             */
/*   Updated: 2024/05/27 22:31:02 by ahibrahi         ###   ########.fr       */
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

void	sleeping(t_philo *philo)
{
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is sleeping\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	my_usleep(philo->time_to_sleep, philo);
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

void	eating(t_philo *philo)
{
	gettimeofday((&philo->curr_time), NULL);
	sem_wait(philo->data->checkin_death_m);
	sem_post(philo->data->checkin_death_m);
	printf("\e[1;32m%ld %d is eating\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	gettimeofday((&philo->eat_time), NULL);
	my_usleep(philo->time_to_eat, philo);
	// gettimeofday((&philo->curr_time), NULL);
	// printf("\e[1;32m%ld %d has ate %d\e[0m\n",
	// 	get_time_cal(&philo->curr_time, &philo->start_time),
	// 	philo->id, philo->num_of_meals++);
	unlock_forks(philo);
	philo->number_of_times--;
}

void	*routin(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	gettimeofday((&philo->start_time), NULL);
	gettimeofday((&philo->eat_time), NULL);
	while (philo->number_of_times != 0)
	{
		gettimeofday(&(philo->curr_time), NULL);
		if (check_death(philo->data) == true)
			return (NULL);
		if (check_forks(philo) == true)
		{
			taking_forks(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		else
			set_dead(philo, philo->id);
	}
	return (NULL);
}
