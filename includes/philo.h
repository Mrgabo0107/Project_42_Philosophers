/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gamoreno <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:20:33 by gamoreno          #+#    #+#             */
/*   Updated: 2023/01/19 19:32:18 by gamoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_phil	t_phil;

typedef struct s_dat
{
	int				data[5];
	t_phil			*philos;
	int				*forks;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	print_mtx;
	pthread_mutex_t	dead_mtx;
	pthread_mutex_t	all_full_mtx;
	int				smone_is_dead;
	int				number_of_full;
	long int		start_time;
}					t_dat;

typedef struct s_phil
{
	t_dat		*initial_data;
	int			index;
	int			is_died;
	int			is_eating;
	int			is_sleeping;
	int			is_thinking;
	long int	last_meal_time;
	long long	meals_taken;
	pthread_t	ph_thrd;
}				t_phil;

/*main*/
void		*routine(void *dat);
/*time*/
long int	get_current_time(void);
long int	get_relative_time(long int start);

/*init*/
int			init_data(int i, char **ag, t_dat *dat);
int			init_all_mtx(t_dat *dat);
int			init_all_data(t_dat *dat);
void		destroy_not_fork_mtx(t_dat *dat);
int			init_forks_mtx(t_dat *dat);

/*Utils*/
int			ag_is_good_number(int ac, char **ag, t_dat *dat);
void		*ft_calloc(size_t nmemb, size_t size);
int			free_ret_one(t_dat *dat);
int			free_ret_zero(t_dat *dat);

/*Errors*/
int			error_1(void);
int			error_2(void);
int			error_3(void);

/*free*/

void		free_dat(t_dat *dat);
void		free_philos(t_dat *dat);
int			free_philos_ret_one(t_dat *dat);
void		free_forks(t_dat *dat);
int			free_forks_ret_one(t_dat *dat);
void		free_forks_mtx(t_dat *dat);
int			free_forks_mtx_ret_one(t_dat *dat);

/*debug*/
void		print_data(t_dat *dat);
void		print_data_and_philo_set(t_phil	*ph);
#endif
