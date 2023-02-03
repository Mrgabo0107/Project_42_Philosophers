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
	if (dat->smone_is_dead == 1)
		return (1);
	pthread_mutex_unlock(&dat->dead_mtx);
	pthread_mutex_lock(&dat->all_full_mtx);
	if (dat->number_of_full == dat->data[0])
		return (1);
	pthread_mutex_unlock(&dat->all_full_mtx);
	return (0);
}

int	still_alive(t_phil *ph)
{
	if (get_relative_time(ph->i_dat->start_time) - ph->last_meal_time > ph->i_dat->data[1])
	{
		pthread_mutex_lock(&ph->i_dat->dead_mtx);
		ph->i_dat->smone_is_dead = 1;
		pthread_mutex_unlock(&ph->i_dat->dead_mtx);
		philo_message(ph, "died");
		return (1);
	}
	if (check_stop(ph->i_dat))
		return (1);
	return (0);
}

static int indx_by_side(t_phil *ph, int side)
{
	if (side == RIGHT)
	{
		// printf("right index philo %d = %d\n", ph->index, (ph->index - 1) % ph->i_dat->data[0]);
		return (ph->index % ph->i_dat->data[0]);
	}
	if (side == LEFT)
		return (ph->index - 1);
	else 
		return (-1);
}

static int if_free_take(t_phil *ph, int i)
{
	int	c;

	c = 0;
	pthread_mutex_lock(&ph->i_dat->forks_mtx[i]);
	if (ph->i_dat->forks[i])
		c = 1;
	else
		ph->i_dat->forks[i] = 1;
	pthread_mutex_unlock(&ph->i_dat->forks_mtx[i]);
	if (c == 1)
		return (1);
	return (0);
}

static int take_one_fork(t_phil *ph, int side)
{
	int i;

	i = indx_by_side(ph, side);
	if (!if_free_take(ph, ph->i_dat->forks[i]))
	{
		if (still_alive(ph))
			return (1);
		philo_message(ph, "has taken a fork");
		// if(side == RIGHT)
		// 	printf("right \n");
		// if(side == LEFT)
		// 	printf("left\n");
		if (side == RIGHT)
			ph->has_r_fork = 1;
		if (side == LEFT)
			ph->has_l_fork = 1;
	}
	return (0);
}

static int take_forks(t_phil *ph)
{
	ph->has_l_fork = 0;
	ph->has_r_fork = 0;
	while (!ph->has_l_fork && !ph->has_r_fork)
	{
		if (still_alive(ph))
			return (1);
		take_one_fork(ph, RIGHT);
		if (still_alive(ph))
			return (1);
		take_one_fork(ph, LEFT);
	}
	return (0);
}

static int leave_forks(t_phil *ph)
{
	if (still_alive(ph))
		return (1);
	pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
	ph->i_dat->forks[indx_by_side(ph, RIGHT)] = 0;
	pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
	if (still_alive(ph))
		return (1);
	pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
	ph->i_dat->forks[indx_by_side(ph, LEFT)] = 0;
	pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
	return (0);
}

static int eat(t_phil *ph)
{
	if (still_alive(ph))
		return (1);
	ph->last_meal_time = get_current_time();
	philo_message(ph, "is eating");
	while (get_current_time() < ph->last_meal_time + ph->i_dat->data[2])
	{
		usleep(1000);
		if (still_alive(ph))
			return (1);
	}
	ph->meals_taken++;
	if (!still_alive(ph) && ph->meals_taken == ph->i_dat->data[4])
	{
		pthread_mutex_lock(&ph->i_dat->all_full_mtx);
		ph->i_dat->number_of_full++;
		pthread_mutex_unlock(&ph->i_dat->all_full_mtx);
	}
	if (leave_forks(ph))
		return (1);
	return (0);
}

static int sleep_think(t_phil *ph)
{
	long int	t;

	if (still_alive(ph))
		return (1);
	t = get_current_time();
	philo_message(ph, "is sleeping");
	while(get_current_time() < t + ph->i_dat->data[3])
	{
		usleep(1000);
		if (still_alive(ph))
			return (1);
	}
	philo_message (ph, "is thinking");
	return (0);
}

int	philo_do_things(t_phil *ph)
{
	if (take_forks(ph))
		return (1);
	if (eat(ph))
		return (1);
	if (sleep_think(ph))
		return (1);
	return (0);
}
