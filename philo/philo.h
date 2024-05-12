/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:29 by aken              #+#    #+#             */
/*   Updated: 2024/05/11 16:13:25 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

typedef struct philo
{
	int				pilo_num;
	struct timeval	eat_time;
	struct timeval	die_time;
	int				time_to_die;
	int				time_to_eat;
	int				number_of_times;
	int				time_to_sleep;
	int				time_to_think;
	pthread_t		thread;
}				t_philo;

typedef struct my_struct
{
	struct timeval	start_time;
	struct timeval	curr_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_2;
	pthread_mutex_t	forks_mutex;
	int				forks;
	bool			philo_died;
	int				philo_num;
	t_philo			**philos;
}				t_my_struct;

// typedef struct threads
// {
// 	int			thread_num;
// 	pthread_t	thread;
// }				t_threads;

long	ft_atoi(char *str);
int		ft_strlen(char *str);
void	*ft_philo(void *philo);
