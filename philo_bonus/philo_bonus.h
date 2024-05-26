/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:29 by aken              #+#    #+#             */
/*   Updated: 2024/05/26 19:06:10 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdbool.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <signal.h>

typedef struct data
{
	sem_t			*forks;
	sem_t			*checkin_death_m;
	int				philo_died;
	int				*pids;
	int				number_of_philosophers;
}				t_data;

typedef struct philo
{
	t_data			*data;
	bool			philo_died;
	int				id;
	// sem_t			*forks;
	// sem_t			*checkin_death_m;
	int				num_of_meals;
	struct timeval	eat_time;
	struct timeval	start_time;
	struct timeval	curr_time;
	long			time_to_die;
	long			time_to_eat;
	long			number_of_times;
	long			time_to_sleep;
}				t_philo;

long		ft_atoi(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
bool		routin(void *philo);
bool		my_usleep(long desired_sleep_us, t_philo *philo);
int			free_philo_array(t_philo **philo);
void		free_data(t_data *data);
bool		check_death(t_data *data);
void		unlock_forks(t_philo *philo);
bool		check_forks(t_philo *philo);
void		taking_forks(t_philo *philo);
bool		eating(t_philo *philo);
bool		sleeping(t_philo *philo);
long		get_time_cal(struct timeval *curr_time,
				struct timeval *start_time);
void		thinking(t_philo *philo);
void		ft_putnbr_fd(long n, int fd);
t_philo		*init_philo(char **av);
t_data		*init_data(char **av);
t_philo		**init_philo_array(t_data *data, char **av);
bool		set_dead(t_philo *philo, int id);
bool		single_philo(t_philo *philo);
