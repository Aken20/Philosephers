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
