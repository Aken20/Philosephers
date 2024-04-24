/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-10 07:09:29 by aken              #+#    #+#             */
/*   Updated: 2024-04-10 07:09:29 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <string.h>
#include <pthread.h>

typedef struct philo
{
    int pilo_num;
    int time_to_die;
    int time_to_eat;
    int number_of_times;
    int time_to_sleep;
    int time_to_think;
    pthread_t   thread;
    void *next_philo;
}               t_philo;

typedef struct  threads
{
    int thread_num;
    pthread_t   thread;
    void *next_thread;
}               t_threads;

long ft_atoi(char *str);
int ft_strlen(char *str);
void    *ft_philo(void *philo);
