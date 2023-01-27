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

void	print_data(t_dat  *ph)
{
	printf("# of filo: %d\n", ph->data[0]);
	printf("time to die: %d\n", ph->data[1]);
	printf("time to eat: %d\n", ph->data[2]);
	printf("timeto sleep: %d\n", ph->data[3]);
	printf("meals per filo: %d\n", ph->data[4]);
}
