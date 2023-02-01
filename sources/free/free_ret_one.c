/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ret_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:30:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/31 17:30:35 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	free_philos_ret_one(t_dat *dat)
{
	free_philos(dat);
	return (1);
}

int	free_forks_ret_one(t_dat *dat)
{
	free_forks(dat);
	return (1);
}

int	free_forks_mtx_ret_one(t_dat *dat)
{
	free_forks_mtx(dat);
	return (1);
}

int	free_ret_one(t_dat *dat)
{
	free_dat(dat);
	return (1);
}
