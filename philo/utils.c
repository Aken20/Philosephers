/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahibrahi <ahibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 07:21:28 by aken              #+#    #+#             */
/*   Updated: 2024/05/14 13:29:50 by ahibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

long	ft_atoi(char *str)
{
	int			s;
	long		aoi;
	int			i;

	i = 0;
	s = 1;
	if (!str || str[i] == 0)
		return (90000000000);
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		++i;
	}
	if (str[i] >= 48 && str[i] <= 57)
		aoi = (str[i++] - 48);
	else
		return (90000000000);
	while (str[i] >= 48 && str[i] <= 57 && i < 9 && aoi < __INT32_MAX__)
		aoi = (aoi * 10) + (str[i++] - 48);
	if (s == -1 || str[i] || aoi == 0)
		return (90000000000);
	return (aoi * s);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	while(str && str[i])
		write(fd, &str[i++],1);
}

long	get_time_cal(struct timeval *curr_time, struct timeval *start_time)
{
	return (((curr_time->tv_sec - start_time->tv_sec) * 1000
			+ ((curr_time->tv_usec - start_time->tv_usec) / 1000)));
}

void	my_usleep(long desired_sleep_us)
{
	struct timeval	start_time;
	struct timeval	end_time;

	gettimeofday(&start_time, 0);
	gettimeofday(&end_time, 0);
	while ((((end_time.tv_sec - start_time.tv_sec) * 1000
				+(end_time.tv_usec / 1000)) - (start_time.tv_usec / 1000))
		< desired_sleep_us / 1000)
	{
		usleep(500);
		gettimeofday(&end_time, 0);
	}
}
