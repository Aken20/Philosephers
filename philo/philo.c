/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024-04-10 07:09:15 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_philo *philo, char **av)
{
    if (ft_atoi(av[1]) == 90000000000 || ft_atoi(av[2]) == 90000000000 || ft_atoi(av[3]) == 90000000000 || ft_atoi(av[4]) == 90000000000)
        exit (1);
    if (av[2])
        philo->time_to_die = ft_atoi(av[2]);
    if (av[3])
        philo->time_to_eat = ft_atoi(av[3]);
    if (av[4])
        philo->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        philo->number_of_times = ft_atoi(av[5]);
    else
        philo->number_of_times = -1;
    philo->time_to_think = 0;
    printf("time_to_die %d\n", philo->time_to_die);
    printf("time_to_eat %d\n", philo->time_to_eat);
    printf("time_to_sleep %d\n", philo->time_to_sleep);
}

t_philo    *init_threads(int num_of_threads, char **av)
{
    int i;
    t_philo *p;
    t_philo *tmp;
    t_philo *thread;

    i = 0;
    p = malloc(sizeof(t_philo));
    p->next_philo = NULL;
    p->pilo_num = i;
    thread = p;
    init_philo(p, av);
    while(++i < num_of_threads)
    {
        tmp = malloc(sizeof(t_philo));
        tmp->pilo_num = i;
        init_philo(tmp, av);
        tmp->next_philo = NULL;
        p->next_philo = tmp;
        p = p->next_philo;
    }
    return (thread);
}

void    *ft_philo(void *p)
{
    t_philo *philo;

    philo = (t_philo *)p;
    printf("philo%d is waiting\n", philo->pilo_num);
    printf("time_to_die %d\n", philo->time_to_die);
    printf("time_to_eat %d\n", philo->time_to_eat);
    printf("time_to_sleep %d\n", philo->time_to_sleep);
    sleep(2);
    printf("philo%d is done\n", philo->pilo_num);
    return (NULL);
}

int main(int ac, char **av)
{
    t_philo     *tmp;
    t_philo     *philo;
    int         i;
    int         num_of_philo;

    if (ac == 4 || ac == 5)
    {
        i = 0;
        printf("%ld\n", ft_atoi(av[1]));
        num_of_philo = ft_atoi(av[1]);
        philo = init_threads(num_of_philo, av);
        tmp = philo;
        while(i++ < num_of_philo)
        {
            printf("init philo%d\n", philo->pilo_num);
            pthread_create(&philo->thread, NULL, &ft_philo, &philo);
            philo = philo->next_philo;
        }
        i = 0;
        philo = tmp;
        while(i++ < num_of_philo)
        {
            pthread_join(philo->thread, NULL);
            philo = philo->next_philo;
        }
        i = 0;
        philo = tmp;
        while(tmp)
        {
            philo = philo->next_philo;
            free(tmp);
            tmp = philo;
        }
    }
    return (0);
}
