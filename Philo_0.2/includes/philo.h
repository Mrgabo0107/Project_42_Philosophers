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
# include <unistd.h>
# define RIGHT 0
# define LEFT 1

typedef struct s_phil	t_phil;

typedef struct s_dat
{
	int				data[5];
	t_phil			*philos;
	int				*forks;
	pthread_mutex_t	*forks_mtx;
	pthread_mutex_t	mtx;
	int				smone_is_dead;
	int				number_of_full;
	long int		start_time;
}					t_dat;

typedef struct s_phil
{
	t_dat		*i_dat;
	int			index;
	int			has_r_fork;
	int			has_l_fork;
	int			is_alive;
	long int	last_meal_time;
	long int	meals_taken;
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
int			init_forks_mtx(t_dat *dat);

/*Utils*/
int			ag_is_good_number(int ac, char **ag, t_dat *dat);
void		*ft_calloc(size_t nmemb, size_t size);
int			free_ret_one(t_dat *dat);
int			free_ret_zero(t_dat *dat);
void		philo_message(t_phil *ph, char *str);

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

/*actions*/
int			check_stop(t_dat *dat);
void		take_forks(t_phil *ph);
void		eat(t_phil *ph);
void		sleep_think(t_phil *ph);
void		still_alive(t_phil *ph);

/*debug*/
void		print_data(t_dat *dat);
void		print_data_and_philo_set(t_phil	*ph);
#endif
