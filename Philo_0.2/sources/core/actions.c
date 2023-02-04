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

static int all_are_full(t_dat *dat)
{
	// printf("num of full %d, dat[0] %d\n", dat->number_of_full, dat->data[0]);
	if (dat->number_of_full == dat->data[0])
		return (0);
	return (1);
}

void	still_alive(t_phil *ph)
{
	if (ph->is_alive && !all_are_full(ph->i_dat))
	{
		ph->i_dat->smone_is_dead = 0;
		// printf ("philo %d | is alive %d, all'r full %d, sm is dead %d\n", ph->index, ph->is_alive, all_are_full(ph->i_dat), ph->i_dat->smone_is_dead);
	}
	// printf("time %ld, last meal %ld, resta %ld, data[1] %d\n", get_current_time(), ph->last_meal_time, get_current_time() - ph->last_meal_time, ph->i_dat->data[1]);
	if (ph->is_alive && get_current_time() - ph->last_meal_time > ph->i_dat->data[1])
	{
		ph->i_dat->smone_is_dead = 0;
		printf("%ld %d died\n", get_relative_time(ph->i_dat->start_time), ph->index);
	}
	ph->is_alive = ph->i_dat->smone_is_dead;
}

static int indx_by_side(t_phil *ph, int side)
{
	if (side == RIGHT)
	{
		return (ph->index % ph->i_dat->data[0]);
	}
	if (side == LEFT)
		return (ph->index - 1);
	else 
		return (-1);
}

void take_one_fork(t_phil *ph, int side)
{
	int i;

	i = indx_by_side(ph, side);
	if (ph->is_alive && !ph->i_dat->forks[i])
	{
		ph->i_dat->forks[i] = 1;
		// philo_message(ph, "has taken a fork");
		printf("%ld %d has taken a fork\n", get_relative_time(ph->i_dat->start_time), ph->index);
		// if (side == RIGHT)
		// 	ph->has_r_fork = 1;
		// if (side == LEFT)
		// 	ph->has_l_fork = 1;
		if (side == RIGHT)
		{
			printf("ph->has_r_fork\n");
			ph->has_r_fork = 1;
		}
		if (side == LEFT)
		{
			ph->has_l_fork = 1;
			printf("ph->has_r_fork\n");
		}
	}
}

void take_forks(t_phil *ph)
{
	ph->has_l_fork = 0;
	ph->has_r_fork = 0;
	while (ph->is_alive && !ph->has_l_fork && !ph->has_r_fork)
	{
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
		take_one_fork(ph, RIGHT);
		pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, RIGHT)]);
		usleep(1);
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
		pthread_mutex_lock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
		take_one_fork(ph, LEFT);
		pthread_mutex_unlock(&ph->i_dat->forks_mtx[indx_by_side(ph, LEFT)]);
	}
}

static void leave_forks(t_phil *ph)
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
	while (ph->is_alive && get_current_time() < ph->last_meal_time + ph->i_dat->data[2])
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

void sleep_think(t_phil *ph)
{
	long int	t;

	t = get_current_time();
	philo_message(ph, "is sleeping");
	while(ph->is_alive && get_current_time() < t + ph->i_dat->data[3])
	{
		usleep(1000);
		pthread_mutex_lock(&ph->i_dat->mtx);
		still_alive(ph);
		pthread_mutex_unlock(&ph->i_dat->mtx);
	}
	philo_message (ph, "is thinking");
}

