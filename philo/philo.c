/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:04:02 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 09:24:18 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	store_nums(int n, char **str, t_infos *infos)
{
	int	i;

	i = 1;
	while (i < n)
	{
		if (ft_atoi(str[i]) == -1 || ft_atoi(str[i]) == 0 
			|| ft_atoi(str[1]) > 200)
		{
			printf("invalid number!\n");
			return (-1);
		}
		i++;
	}
	infos->num_philos = ft_atoi(str[1]);
	infos->time_to_die = ft_atoi(str[2]);
	infos->time_to_eat = ft_atoi(str[3]);
	infos->time_to_sleep = ft_atoi(str[4]);
	infos->times_must_eat = -1;
	if (n == 6)
		infos->times_must_eat = ft_atoi(str[5]);
	return (0);
}

int	check_input(int n, char **str, t_infos *infos)
{
	int	i;

	if (n < 5 || n > 6)
	{
		printf("Incorrect number of args!\n");
		return (1);
	}
	i = 1;
	while (i < n)
	{
		if (is_num(str[i]) != 0)
		{
			printf("invalid number!\n");
			return (2);
		}
		i++;
	}
	if (store_nums(n, str, infos) != 0)
		return (-1);
	return (0);
}

void	help_init_philo(t_infos *infos, int *i)
{
	infos->philos[*i].id = *i + 1;
	infos->philos[*i].meal_count = 0;
	infos->philos[*i].last_meal_tm = 0;
	infos->philos[*i].l_fork = &infos->forks[*i];
	infos->philos[*i].r_fork = &infos->forks[(*i + 1) % infos->num_philos];
	infos->philos[*i].infos = infos;
}

int	init_philo(t_infos *infos)
{
	int	i;

	i = 0;
	infos->dead = 0;
	infos->start_time = curr_time_ms();
	infos->forks = malloc(sizeof(pthread_mutex_t) * (infos->num_philos));
	if (infos->forks == NULL)
		return (-1);
	i = -1;
	while (++i < infos->num_philos)
		pthread_mutex_init(&infos->forks[i], NULL);
	infos->philos = malloc(sizeof(t_philo) * (infos->num_philos));
	if (infos->philos == NULL)
		return (1);
	pthread_mutex_init(&infos->print_log, NULL);
	pthread_mutex_init(&infos->death_lock, NULL);
	pthread_mutex_init(&infos->meal_lock, NULL);
	i = -1;
	while (++i < infos->num_philos)
		help_init_philo(infos, &i);
	return (0);
}
