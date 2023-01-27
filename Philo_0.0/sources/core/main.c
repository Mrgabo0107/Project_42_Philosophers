/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:19:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/19 19:25:51 by gamoreno         ###   ########.fr       */
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

void	*routine(void *dat)
{
	t_dat  *dat_r;

	dat_r = (t_dat  *)dat;
	pthread_mutex_lock(&(dat_r->print_mtx));
	printf("relative time %ld\n", get_relative_time(dat_r->start_time));
	pthread_mutex_unlock(&(dat_r->print_mtx));
	return (NULL);
}


static int	join_philosophers(t_dat *dat)
{
	int	i;

	i = 0;
	while (i < dat->data[0])
	{
		if (pthread_join(dat->philos[i], NULL))
			return (1);
		i++;
	}
	return (0);
}


int	main(int ac, char **ag)
{
	t_dat 	*dat;

	dat = (t_dat  *)ft_calloc(1, sizeof(t_dat));
	if (!dat)
		return (1);
	if (parse(ac, ag, dat))
		return (free_ret_one(dat));
	init_all_mtx(dat);
	if (init_all_data(dat))
		return (free_ret_one(dat));
	if (join_philosophers(dat))
		return (free_ret_one(dat));
	destroy_not_fork_mtx(dat);
	return (free_ret_zero(dat));
}
