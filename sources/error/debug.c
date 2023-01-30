/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 17:00:07 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/24 17:00:11 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

void	print_data(t_dat  *dat)
{
	printf("# of filo: %d\n", dat->data[0]);
	printf("time to die: %d\n", dat->data[1]);
	printf("time to eat: %d\n", dat->data[2]);
	printf("timeto sleep: %d\n", dat->data[3]);
	printf("meals per filo: %d\n", dat->data[4]);
	printf("someone is dead: %d\n", dat->smone_is_dead);
	printf("all are full: %d\n", dat->all_are_full);
}

void	print_data_and_philo_set(t_phil	*ph)
{
	printf("----------------------------------\n");
	printf("----------------------------------\n");
	printf("PHILO NUMBER %d\n", ph->index);
	printf("----------------------------------\n");
	printf("----------------------------------\n");
	printf("check data:\n");
	printf("------\n");
	print_data(ph->initial_data);
	printf("------\n");
	printf("is died = %d\n", ph->is_died);
	printf("is eating = %d\n", ph->is_eating);
	printf("is sleeping = %d\n", ph->is_sleeping);
	printf("is thinking = %d\n", ph->is_thinking);
	printf("has l fork = %d\n", ph->has_l_fork);
	printf("has r fork = %d\n", ph->has_r_fork);
	printf("is thinking = %lld\n", ph->meals_taken);
}