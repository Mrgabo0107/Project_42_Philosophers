/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 18:26:10 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/23 18:26:13 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

int	error_1(void)
{
	printf("Philosophers: Invalid number of arguments.\n");
	return (1);
}

int	error_2(void)
{
	printf("Philosophers: Invalid arguments.\n");
	printf("Launch: ./philo <number of philosophers>, ");
	printf("<time to die>, ");
	printf("<time to eat>, ");
	printf("<time to sleep>, ");
	printf("<(optional)number of meals per philospher>\n");
	printf("all must be non negative integers.\n");
	return (1);
}

int	error_3(void)
{
	printf("Philosophers: The number passed as parameter ");
	printf("has to fit in an int\n");
	printf("Is better to try with little numbers anyaway\n");
	return (1);
}
