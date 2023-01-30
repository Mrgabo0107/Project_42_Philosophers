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

int	free_philos_ret_one(t_dat  *dat)
{
	free_philos(dat);
	return (1);
}

void free_philos(t_dat *dat)
{
	int	i;

	i = 0;
	if (dat->philos)
	{
		while (i < dat->data[0])
		{
			if (dat->philos[i])
				free(dat->philos[i]);
		}
		free(dat->philos);
	}
}

int	free_forks_ret_one(t_dat  *dat)
{
	free_forks(dat);
	return (1);
}

void free_forks(t_dat *dat)
{
	int	i;

	i = 0;
	if (dat->forks)
	{
		while (i < dat->data[0])
		{
			if (dat->forks[i])
				free(dat->forks[i]);
		}
		free(dat->forks);
	}
}

int	free_forks_mtx_ret_one(t_dat  *dat, int last_succes)
{
    int i;

    i = 0;
    while (i < last_succes)
    {
       pthread_mutex_destroy(dat->forks_mtx[i]);
       i++;
    }
	free_forks_mtx(dat);
	return (1);
}

void free_forks_mtx(t_dat *dat)
{
	int	i;

	i = 0;
	if (dat->forks_mtx)
	{
		while (i < dat->data[0])
		{
			if (dat->forks_mtx[i])
            {
	            pthread_mutex_destroy(dat->forks_mtx[i]);
				free(dat->forks_mtx[i]);
            }
		}
		free(dat->forks);
	}
}


static void free_dat(t_dat *dat)
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

int	free_ret_zero(t_dat  *dat)
{
	free_dat(dat);
	return (0);
}

int	free_ret_one(t_dat  *dat)
{
	free_dat(dat);
	return (1);
}