/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:09:15 by aken              #+#    #+#             */
/*   Updated: 2024/05/26 19:08:04 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		exit(EXIT_FAILURE);
	}
	else
	{
		free_philo_array(philo_array);
		exit(EXIT_SUCCESS);
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
			exit(EXIT_FAILURE);
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
				if (routin(philo_array[i]) == false)
					ft_exit(philo_array);
			}
		}
		i = -1;
		while (++i < data->number_of_philosophers)
		{
			waitpid(philo_array[i]->id, NULL, 0);
			if (WIFEXITED(philo_array[++i]->id) && WEXITSTATUS(philo_array[i]->id))
			{
				while (++i < data->number_of_philosophers)
					kill(philo_array[i]->id, SIGKILL);
				ft_exit(philo_array);
				return (1);
			}
			ft_exit(philo_array);
		}
		ft_exit(philo_array);
	}
	return (0);
}
