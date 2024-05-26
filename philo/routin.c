/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:34:00 by aken              #+#    #+#             */
/*   Updated: 2024/05/26 21:56:08 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	taking_forks(t_philo *philo)
{
	if (check_death(philo->data) == true)
		return ;
	pthread_mutex_lock(&(philo->data->mutex));
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;33m%ld %d has taken a fork\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->mutex));
}

void	sleeping(t_philo *philo)
{
	if (check_death(philo->data) == true)
		return ;
	pthread_mutex_lock(&(philo->data->mutex));
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is sleeping\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->mutex));
	my_usleep(philo->time_to_sleep, philo);
	if (check_death(philo->data) == true)
		return ;
}

void	thinking(t_philo *philo)
{
	if (check_death(philo->data) == true)
		return ;
	pthread_mutex_lock(&(philo->data->mutex));
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;30m%ld %d is thinking\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	pthread_mutex_unlock(&(philo->data->mutex));
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->mutex));
	gettimeofday((&philo->curr_time), NULL);
	printf("\e[1;32m%ld %d is eating\e[0m\n",
		get_time_cal(&philo->curr_time, &philo->start_time),
		philo->id);
	gettimeofday((&philo->eat_time), NULL);
	pthread_mutex_unlock(&(philo->data->mutex));
	my_usleep(philo->time_to_eat, philo);
	if (check_death(philo->data) == true)
		return ;
	unlock_forks(philo->data, philo->id - 1);
	philo->number_of_times--;
}

void	*routin(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	pthread_mutex_lock(&(philo->data->mutex));
	gettimeofday((&philo->start_time), NULL);
	gettimeofday((&philo->eat_time), NULL);
	pthread_mutex_unlock(&(philo->data->mutex));
	while (philo->number_of_times)
	{
		pthread_mutex_lock(&(philo->data->mutex));
		gettimeofday(&(philo->curr_time), NULL);
		pthread_mutex_unlock(&(philo->data->mutex));
		if (check_forks(philo->data, philo->id - 1, philo) == true)
		{
			taking_forks(philo);
			eating(philo);
			sleeping(philo);
			thinking(philo);
		}
		set_dead(philo, philo->id);
		if (check_death(philo->data) == true)
			return (NULL);
	}
	return (NULL);
}
