/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 01:33:31 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/07 02:02:43 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	all_are_full(t_dat *dat)
{
	if (dat->number_of_full == dat->data[0])
		return (0);
	return (1);
}

void	still_alive(t_phil *ph)
{
	if (ph->is_alive && get_current_time()
		- ph->last_meal_time > ph->i_dat->data[1])
	{
		ph->i_dat->smone_is_dead = 0;
		printf("%ld %d died\n",
			get_relative_time(ph->i_dat->start_time), ph->index);
	}
	if (ph->is_alive && !all_are_full(ph->i_dat))
	{
		ph->i_dat->smone_is_dead = 0;
	}
	ph->is_alive = ph->i_dat->smone_is_dead;
}

int	indx_by_side(t_phil *ph, int side)
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
