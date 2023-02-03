/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:40:59 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/31 17:41:01 by gamoreno         ###   ########.fr       */
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

void	destroy_not_fork_mtx(t_dat *dat)
{
	pthread_mutex_destroy(&dat->print_mtx);
	pthread_mutex_destroy(&dat->dead_mtx);
	pthread_mutex_destroy(&dat->all_full_mtx);
}
