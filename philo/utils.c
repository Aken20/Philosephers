/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aken <aken@student.42.fr>                  #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-04-10 07:21:28 by aken              #+#    #+#             */
/*   Updated: 2024-04-10 07:21:28 by aken             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_strlen(char *str)
{
    int len;

    len = 0;
    while (str && str[len])
        len++;
    return (len);
    
}

long ft_atoi(char *str)
{
    int res;
    int sign;
    int len;

    res = 0;
    len = ft_strlen(str);
    sign = 1;
    if (len == 0)
        return (90000000000);
    if (str[0] == '-')
        sign *= -1;
    len--;
    while (str[len] && str[len] >= 48 && str[len] <= 57 && res < __INT32_MAX__)
    {
        res += (res * 10) + (str[len] - 48);
        len--;
    }
    if (str[len] == '-' || str[len] == '+')
        len--;
    if (str[len] || res > __INT32_MAX__ || sign == -1)
        return (90000000000);
    return (res);
}
