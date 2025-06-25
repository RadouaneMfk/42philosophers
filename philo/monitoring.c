/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:24:49 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 09:59:58 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->infos->death_lock);
	if (philo->infos->dead)
	{
		pthread_mutex_unlock(&philo->infos->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->infos->death_lock);
	return (0);
}

int	finish_eat(t_philo *philo)
{
	int	i;
	int	finish;

	i = -1;
	finish = 0;
	if (philo->infos->times_must_eat == -1)
		return (0);
	while (++i < philo->infos->num_philos)
	{
		pthread_mutex_lock(&philo->infos->meal_lock);
		if (philo->infos->philos[i].meal_count >= philo->infos->times_must_eat)
			++finish;
		pthread_mutex_unlock(&philo->infos->meal_lock);
	}
	pthread_mutex_lock(&philo->infos->death_lock);
	if (finish == philo->infos->num_philos)
	{
		philo->infos->dead = 1;
		pthread_mutex_unlock(&philo->infos->death_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->infos->death_lock);
	return (0);
}

void	death_print(t_philo	*philo)
{
	philo->infos->dead = 1;
	pthread_mutex_unlock(&philo->infos->death_lock);
	pthread_mutex_lock(&philo->infos->print_log);
	printf("%zu %d %s\n", curr_time_ms() - philo->infos->start_time, 
		philo->id, "died");
	pthread_mutex_unlock(&philo->infos->print_log);
}

void	*monitoring_death(void *arg)
{
	t_philo	*philo;
	size_t	time;
	int		i;

	philo = arg;
	while (1)
	{
		i = -1;
		while (++i < philo->infos->num_philos)
		{
			pthread_mutex_lock(&philo->infos->death_lock);
			if (philo->infos->dead)
				return (pthread_mutex_unlock(&philo->infos->death_lock), NULL);
			pthread_mutex_lock(&philo->infos->meal_lock);
			time = philo->infos->philos[i].last_meal_tm;
			pthread_mutex_unlock(&philo->infos->meal_lock);
			if ((int)(curr_time_ms() - time) > philo->infos->time_to_die)
				return (death_print(philo), NULL);
			pthread_mutex_unlock(&philo->infos->death_lock);
		}
		if (finish_eat(philo))
			return (NULL);
	}
	return (NULL);
}
