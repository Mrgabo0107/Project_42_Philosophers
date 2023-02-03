/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:40:49 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/31 17:40:52 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	set_philo(t_dat *dat, t_phil *ph, int i)
{
	ph->i_dat = dat;
	ph->index = i + 1;
	ph->has_l_fork = 0;
	ph->has_r_fork = 0;
	ph->meals_taken = 0;
	ph->last_meal_time = 0;
	if (pthread_create(&ph->ph_thrd, NULL, &routine, (void *)ph))
		return (1);
	return (0);
}

static int	init_philos(t_dat *dat)
{
	int	i;

	i = 0;
	dat->philos = (t_phil *)ft_calloc(dat->data[0], sizeof(t_phil));
	if (!dat->philos)
		return (1);
	dat->start_time = get_current_time();
	while (i < dat->data[0])
	{
		if (set_philo(dat, &dat->philos[i], i))
			return (free_philos_ret_one(dat));
		i++;
	}
	return (0);
}

static int	init_forks(t_dat *dat)
{
	int	i;

	i = 0;
	dat->forks = (int *)ft_calloc(dat->data[0], sizeof(int));
	if (!dat->forks)
		return (1);
	while (i < dat->data[0])
	{
		dat->forks[i] = 0;
		i++;
	}
	return (0);
}

int	init_forks_mtx(t_dat *dat)
{
	int	i;

	i = 0;
	dat->forks_mtx = (pthread_mutex_t *)ft_calloc(dat->data[0],
			sizeof(pthread_mutex_t));
	if (!dat->forks_mtx)
		return (1);
	while (i < dat->data[0])
	{
		if (pthread_mutex_init(&dat->forks_mtx[i], NULL))
			return (free_forks_mtx_ret_one(dat));
		i++;
	}
	return (0);
}

int	init_all_data(t_dat *dat)
{
	dat->number_of_full = 0;
	dat->smone_is_dead = 0;
	if (init_forks(dat))
		return (1);
	if (init_philos(dat))
		return (1);
	return (0);
}
