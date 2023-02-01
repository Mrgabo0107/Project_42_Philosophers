/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:10:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/31 22:10:13 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int check_stop(t_dat *dat)
{
	pthread_mutex_lock(&dat->dead_mtx);
	if (dat->smone_is_dead = 1)
		return (1);
	pthread_mutex_unlock(&dat->dead_mtx);
	pthread_mutex_lock(&dat->all_full_mtx);
	if (dat->number_of_full = dat->data[0])
		return (1);
	pthread_mutex_unlock(&dat->all_full_mtx);
	return (0);
}

int eat(t_phil *ph)
{
	pthread_mutex_lock(&ph->initial_data->forks_mtx[ph->index % ph->initial_data->data[0]]);
	if (ph->initial_data->forks[ph->index % ph->initial_data->data[0]])
	pthread_mutex_unlock(&ph->initial_data->forks_mtx[ph->index % ph->initial_data->data[0]]);
}


