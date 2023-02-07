/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:36:28 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/27 16:36:30 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	free_philos(t_dat *dat)
{
	if (dat->philos)
		free(dat->philos);
}

void	free_forks(t_dat *dat)
{
	if (dat->forks)
		free(dat->forks);
}

void	free_forks_mtx(t_dat *dat)
{
	int	i;

	i = 0;
	if (dat->forks_mtx)
	{
		while (i < dat->data[0])
		{
			pthread_mutex_destroy(&dat->forks_mtx[i]);
			i++;
		}
		free(dat->forks_mtx);
	}
}

void	free_dat(t_dat *dat)
{
	if (dat)
	{
		if (dat->philos)
			free_philos(dat);
		if (dat->forks)
			free_forks(dat);
		if (dat->forks_mtx)
			free_forks_mtx(dat);
		free(dat);
	}
}

int	free_ret_zero(t_dat *dat)
{
	free_dat(dat);
	return (0);
}
