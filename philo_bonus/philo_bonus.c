/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/28 08:42:54 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check(void *p)
{
	t_philo		*philo;

	philo = (t_philo *)p;
	sem_wait(philo->data->terminit_child);
	free_data(philo->data);
	free(philo);
	exit(1);
}

void	my_waitpid(t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			// waitpid(data->pids[i], NULL, 0);
			if (WIFEXITED(data->pids[i]))
			{
				printf("i: %d\n", data->pids[i]);
				if (WEXITSTATUS(data->pids[i]))
				{
					i = -1;
					printf("i: %d\n", WEXITSTATUS(data->pids[i]));
					while (++i < data->number_of_philosophers)
						sem_post(data->terminit_child);
					return ;
				}
				return ;
			}
		}
	}
}

void	unlock_forks(t_philo *philo)
{
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

bool	check_forks(t_philo *philo)
{
	sem_wait(philo->data->forks);
	sem_wait(philo->data->forks);
	return (true);
}

void	ft_exit(t_philo **philo_array)
{
	int	i;

	if (philo_array[0]->data->philo_died)
	{
		i = philo_array[0]->data->philo_died - 1;
		ft_putstr_fd("\033[9;3;31m", 1);
		ft_putnbr_fd(get_time_cal(&philo_array[i]->curr_time,
				&philo_array[i]->start_time), 1);
		ft_putstr_fd(" ", 1);
		ft_putnbr_fd(philo_array[0]->data->philo_died, 1);
		ft_putstr_fd(" died\033[0m\n", 1);
		free_philo_array(philo_array);
		exit(1);
	}
	else
	{
		free_philo_array(philo_array);
		exit(0);
	}
}

bool	check_death(t_data *data)
{
	if (data->philo_died != 0)
		return (true);
	return (false);
}

int	main(int ac, char **av)
{
	t_philo		**philo_array;
	t_data		*data;
	int			i;

	if (ac == 5 || ac == 6)
	{
		i = -1;
		data = init_data(av);
		if (data->number_of_philosophers > 200)
		{
			ft_putstr_fd("Do Not Enter More than 200", STDERR_FILENO);
			free_data(data);
			exit(1);
		}
		philo_array = init_philo_array(data, av);
		if (!philo_array)
			return (1);
		while (++i < data->number_of_philosophers)
		{
			philo_array[i]->id = fork();
			if (philo_array[i]->id == 0)
			{
				philo_array[i]->id = i + 1;
				pthread_create(&(philo_array[i]->check_death), NULL,
					check, philo_array[i]);
				pthread_create(&(philo_array[i]->routin_thread), NULL,
					routin, philo_array[i]);
				pthread_join(philo_array[i]->check_death, NULL);
				pthread_join(philo_array[i]->routin_thread, NULL);
				exit(0);
			}
			// data->pids[i] = philo_array[i]->id;
		}
		my_waitpid(data);
		ft_exit(philo_array);
	}
	return (0);
}
