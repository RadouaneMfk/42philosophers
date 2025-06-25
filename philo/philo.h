/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:04:04 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 09:44:54 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	size_t			last_meal_tm;
	struct s_infos	*infos;
}	t_philo;

typedef struct s_infos
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	int				dead;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	death_lock;
	size_t			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_log;
	t_philo			*philos;
}	t_infos;

long	ft_atoi(const char *str);
int		is_num(char *str);
int		store_nums(int n, char **str, t_infos *infos);
int		check_input(int n, char **str, t_infos *infos);
size_t	curr_time_ms(void);
int		init_philo(t_infos *infos);
void	log_action(t_philo *philo, char *action);
void	ft_usleep(size_t ms, t_infos *infos);
int		check_death(t_philo *philo);
void	*monitoring_death(void *arg);
void	*routine(void *arg);

#endif