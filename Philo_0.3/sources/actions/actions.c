/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:10:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/07 02:12:27 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static void	take_one_fork(t_phil *ph, int side)
{
	int	i;

	i = indx_by_side(ph, side);
	if (ph->is_alive && !ph->i_dat->forks[i])
	{
		ph->i_dat->forks[i] = 1;
		printf("%ld philo%d has taken a fork\n",
			get_relative_time(ph->i_dat->start_time), ph->index);
		if (side == RIGHT)
			ph->has_r_fork = 1;
		else if (side == LEFT)
			ph->has_l_fork = 1;
	}
}

void	take_forks(t_phil *ph)
{
	ph->has_l_fork = 0;
	ph->has_r_fork = 0;
	while (ph->is_alive && (!ph->has_l_fork || !ph->has_r_fork))
	{
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
		take_one_fork(ph, RIGHT);
		pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		usleep(1);
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
		take_one_fork(ph, LEFT);
		pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
		pthread_mutex_unlock(&ph->i_dat->mtx);
	}
}

static void	leave_forks(t_phil *ph)
{
	pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
	ph->i_dat->forks[indx_by_side(ph, RIGHT)] = 0;
	pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
	pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
	ph->i_dat->forks[indx_by_side(ph, LEFT)] = 0;
	pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
}

void	eat(t_phil *ph)
{
	ph->last_meal_time = get_current_time();
	philo_message(ph, "is eating");
	while (ph->is_alive && get_current_time()
		< ph->last_meal_time + ph->i_dat->data[2])
	{
		usleep(1000);
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
	}
	ph->meals_taken++;
	if (ph->is_alive && (ph->meals_taken == ph->i_dat->data[4]))
	{
		pthread_mutex_lock(&ph->i_dat->mtx);
		ph->i_dat->number_of_full++;
		pthread_mutex_unlock(&ph->i_dat->mtx);
	}
	leave_forks(ph);
}

void	sleep_think(t_phil *ph)
{
	long int	t;

	t = get_current_time();
	philo_message(ph, "is sleeping");
	while (ph->is_alive && get_current_time() < t + ph->i_dat->data[3])
	{
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		usleep(1000);
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
	}
	philo_message (ph, "is thinking");
}
