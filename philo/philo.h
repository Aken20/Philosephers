/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:29 by aken              #+#    #+#             */
/*   Updated: 2024/05/22 12:22:17 by ahibrahi         ###   ########.fr       */
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

typedef struct my_struct
{
	int				*forks;
	pthread_mutex_t	*mutex_array;
	struct timeval	start_time;
	struct timeval	curr_time;
	pthread_mutex_t	mutex;
	pthread_mutex_t	mutex_2;
	bool			philo_died;
	int				philo_num;
}				t_my_struct;

typedef struct philo
{
	t_my_struct		*my_struct;
	bool			philo_died;
	int				pilo_num;
	int				num_of_meals;
	struct timeval	eat_time;
	struct timeval	die_time;
	long			time_to_die;
	long			time_to_eat;
	long			number_of_times;
	long			time_to_sleep;
	long			time_to_think;
	pthread_t		thread;
}				t_philo;

long		ft_atoi(char *str);
int			ft_strlen(char *str);
void		*ft_philo(void *philo);
void		my_usleep(long desired_sleep_us);
int			philo_free(t_philo	***philo);
t_philo		*init_philo(char **av);
t_my_struct	*init_threads(int num_of_threads);
t_philo		**init_phils_array(int num_of_threads, char **av);


