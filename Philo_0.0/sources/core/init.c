/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:24:23 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/24 16:28:34 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static long int	ft_atoli_fit_int(const char *nptr)
{
	long int	i;
	long int	j;

	i = 0;
	j = 0;
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		j += nptr[i] - 48;
		if (j > INT_MAX)
			return (-1);
		j *= 10;
		i++;
	}
	return (j / 10);
}

int	init_data(int i, char **ag, t_dat *dat)
{
	dat->data[i - 1] = (int)ft_atoli_fit_int(ag[i]);
	if (dat->data[i - 1] == -1)
		return (error_3());
	if (!dat->data[i - 1])
		return (1);
	return (0);
}

static int set_philo(t_dat *dat, t_phil *ph, int i)
{
	ph->initial_data = dat;
	ph->index = i + 1;
	ph->is_died = 0;
	ph->is_eating = 0;
	ph->is_slepping = 0;
	ph->is_thinking = 0;
	ph->has_l_fork = 0;
	ph->has_r_fork = 0;
	ph->current_time = 0;
	ph->meals_taken = 0;
	if (pthread_create(&ph->ph_thrd, NULL, &routine, (void *)dat))
		return (1);
	return (0);
}
static int	init_philos(t_dat  *dat)
{
	int	i;

	i = 0;
	dat->philos = (t_phil **)ft_calloc(dat->data[0], sizeof(t_phil *));
	if (!dat->philos)
		return (1);
	while (i < dat->data[0])
	{
		dat->philos[i] = (t_phil *)ft_calloc(1, sizeof(t_phil));
		if (!dat->philos[i])
			return (free_philos_ret_one(dat));
		if (set_philo(dat, dat->philos[i], i));
			return (free_philos_ret_one(dat));
		i++;
	}
	return (0);
}

static int	init_forks(t_dat *dat)
{
	int	i;

	i = 0;
	dat->forks = (bool **)ft_calloc(dat->data[0], sizeof(bool *));
	if (!dat->forks)
		return (1);
	while (i < dat->data[0])
	{
		dat->forks[i] = (bool *)ft_calloc(1, sizeof(bool));
		if (!dat->forks[i])
			return (free_forks_ret_one(dat));
		dat->forks[i] = 0;
		i++;
	}
	return (0);
}

static int	init_forks_mtx(t_dat *dat)
{
	int	i;

	i = 0;
	dat->forks = (pthread_mutex_t **)ft_calloc(dat->data[0], sizeof(pthread_mutex_t *));
	if (!dat->forks)
		return (1);
	while (i < dat->data[0])
	{
		dat->forks[i] = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		if (!dat->forks[i])
			return (free_forks_mtx_ret_one(dat, i));
		if (pthread_mutex_init(&dat->forks_mtx[i], NULL));
			return (free_forks_mtx_ret_one(dat, i));
		i++;
	}
	return (0);
}

int	init_all_data(t_dat *dat)
{
	if (init_philos(dat))
		return (1);
	if (init_forks(dat))
		return (1);
	dat->smone_is_dead = 0;
	dat->all_are_full = 0;
	return (0);
}

int	init_all_mtx(t_dat *dat)
{
	if (init_forks_mtx(dat))
		return (1);
	if (pthread_mutex_init(&dat->print_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&dat->dead_mtx, NULL))
		return (1);
	if (pthread_mutex_init(&dat->all_full_mtx, NULL))
		return (1);
	return (0);
}

void destroy_not_fork_mtx(t_dat *dat)
{
	pthread_mutex_destroy(&dat->print_mtx);
	pthread_mutex_destroy(&dat->dead_mtx);
	pthread_mutex_destroy(&dat->all_full_mtx);
}
