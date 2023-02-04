/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:02:09 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/24 16:02:11 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

static int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ag_is_good_number(int ac, char **ag, t_dat *dat)
{
	int	i;
	int	j;

	i = 1;
	if (ac == 5)
		dat->data[4] = -1;
	while (i < ac)
	{
		j = 0;
		while (ag[i][j])
		{
			if (!ft_isdigit(ag[i][j]))
				return (1);
			j++;
		}
		if (init_data(i, ag, dat))
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	i = 0;
	str = (char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*p;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	p = (void *)malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, nmemb * size);
	return ((void *)p);
}

void	philo_message(t_phil *ph, char *str)
{
	pthread_mutex_lock(&ph->i_dat->mtx);
	still_alive(ph);
	if (ph->is_alive)
	{
		printf("%ld %d ", get_relative_time(ph->i_dat->start_time), ph->index);
		printf("%s || philo %d has taken %ld meals\n", str, ph->index, ph->meals_taken);
	}
	pthread_mutex_unlock(&ph->i_dat->mtx);
}
