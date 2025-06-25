/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:02:17 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 09:33:08 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(size_t ms, t_infos *infos)
{
	size_t	start;

	start = curr_time_ms();
	while (curr_time_ms() - start < ms)
	{
		usleep(100);
		pthread_mutex_lock(&infos->death_lock);
		if (infos->dead)
		{
			pthread_mutex_unlock(&infos->death_lock);
			return ;
		}
		pthread_mutex_unlock(&infos->death_lock);
	}
}

void	clear_threads(t_infos *infos)
{
	int	i;

	i = 0;
	while (i < infos->num_philos)
	{
		pthread_mutex_destroy(&infos->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&infos->meal_lock);
	pthread_mutex_destroy(&infos->print_log);
	pthread_mutex_destroy(&infos->death_lock);
	free(infos->philos);
	free(infos->forks);
}

int	main(int ac, char *av[])
{
	t_infos		infos;
	pthread_t	monitor;
	int			i;

	if (check_input(ac, av, &infos) != 0)
		return (-1);
	if (init_philo(&infos) != 0)
		return (1);
	i = 0;
	pthread_create(&monitor, NULL, monitoring_death, infos.philos);
	while (i < infos.num_philos)
	{
		pthread_create(&infos.philos[i].thread, NULL, 
			routine, &infos.philos[i]);
		i++;
	}
	pthread_join(monitor, NULL);
	i = 0;
	while (i < infos.num_philos)
	{
		pthread_join(infos.philos[i].thread, NULL);
		i++;
	}
	clear_threads(&infos);
}
