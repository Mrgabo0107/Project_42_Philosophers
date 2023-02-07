/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <gamoreno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:19:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/02/07 21:24:07 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	parse(int ac, char **ag, t_dat *dat)
{
	if (ac != 5 && ac != 6)
		return (error_1());
	if (ag_is_good_number(ac, ag, dat))
		return (error_2());
	return (0);
}

void	*routine(void *ph)
{
	t_phil	*ph_r;

	ph_r = (t_phil *)ph;
	if (ph_r->index % 2 == 0)
		usleep(10000);
	while (ph_r->is_alive)
	{
		take_forks(ph);
		eat(ph);
		sleep_think(ph);
	}
	return (NULL);
}

static int	join_philosophers(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->data[0])
	{
		if (pthread_join(dat->philos[i].ph_thrd, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int ac, char **ag)
{
	t_dat	*dat;

	dat = (t_dat *)ft_calloc(1, sizeof(t_dat));
	if (!dat)
		return (1);
	if (parse(ac, ag, dat))
		return (free_ret_one(dat));
	init_all_mtx(dat);
	if (init_all_data(dat))
		return (free_ret_one(dat));
	if (join_philosophers(dat))
		return (free_ret_one(dat));
	pthread_mutex_destroy(&dat->mtx);
	return (free_ret_zero(dat));
}
