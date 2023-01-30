/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 23:58:07 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/24 23:58:10 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

long int	get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long int	get_relative_time(long int start)
{
	struct timeval	tv;

	if(gettimeofday(&tv, NULL))
		return (-1);
	return((tv.tv_sec * 1000 + tv.tv_usec /1000) - start);
}