/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:34:00 by aken              #+#    #+#             */
/*   Updated: 2024/05/30 08:28:59 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	set_dead(philo);
	if (check_death(philo->data) == true)
	{
		unlock_forks(philo->data, philo->id - 1);
		gettimeofday(&(philo->curr_time), NULL);
		return ;
	}
	pthread_mutex_lock(&(philo->data->m_print));
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(philo->curr_time, philo->start_time),
		philo->id);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(philo->curr_time, philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->m_print));
}

void	sleeping(t_philo *philo)
{
	set_dead(philo);
	if (check_death(philo->data) == true)
		return ;
	pthread_mutex_lock(&(philo->data->m_print));
	printf("\e[1;30m%ld %d is sleeping\e[0m\n",
		get_time_cal(philo->curr_time, philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->m_print));
	my_usleep(philo->time_to_sleep, philo);
	set_dead(philo);
	if (check_death(philo->data) == true)
		return ;
}

void	thinking(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->m_print));
	printf("\e[1;30m%ld %d is thinking\e[0m\n",
		get_time_cal(philo->curr_time, philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->m_print));
}

void	eating(t_philo *philo)
{
	set_dead(philo);
	if (check_death(philo->data) == true)
		return ;
	pthread_mutex_lock(&(philo->data->m_print));
	printf("\e[1;32m%ld %d is eating\e[0m\n",
		get_time_cal(philo->curr_time, philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->m_print));
	gettimeofday(&(philo->eat_time), NULL);
	my_usleep(philo->time_to_eat, philo);
	unlock_forks(philo->data, philo->id - 1);
	set_dead(philo);
	if (check_death(philo->data) == true)
		return ;
	philo->number_of_times--;
}

void	*routin(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	gettimeofday(&(philo->start_time), NULL);
	gettimeofday(&(philo->eat_time), NULL);
	if (philo->id % 2 == 0)
		my_usleep(philo->time_to_eat / 2, philo);
	while (philo->number_of_times)
	{
		gettimeofday(&(philo->curr_time), NULL);
		if (check_forks(philo->data, philo->id - 1, philo))
		{
			take_forks(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		set_dead(philo);
		if (check_death(philo->data) == true)
			return (NULL);
	}
	return (NULL);
}

// void	*routin(void *p)
// {
// 	t_philo		*philo;

// 	philo = (t_philo *)p;
// 	gettimeofday(&(philo->start_time), NULL);
// 	gettimeofday(&(philo->eat_time), NULL);
// 	if (philo->id % 2 == 0)
// 		my_usleep(philo->time_to_eat / 2, philo);
// 	while (check_death(philo->data) == false)
// 	{
// 		gettimeofday(&(philo->curr_time), NULL);
// 		if (philo->number_of_times)
// 		{
// 			if (check_forks(philo->data, philo->id - 1, philo))
// 			{
// 				take_forks(philo);
// 				eating(philo);
// 				sleeping(philo);
// 				thinking(philo);
// 			}
// 		}
// 		set_dead(philo);
// 	}
// 	return (NULL);
// }
