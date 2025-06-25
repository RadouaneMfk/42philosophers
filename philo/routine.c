/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 09:21:04 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 10:41:04 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	log_action(philo, "has taken a fork");
	if (check_death(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	pthread_mutex_lock(philo->r_fork);
	log_action(philo, "has taken a fork");
	log_action(philo, "is eating");
	pthread_mutex_lock(&philo->infos->meal_lock);
	philo->last_meal_tm = curr_time_ms();
	philo->meal_count++;
	pthread_mutex_unlock(&philo->infos->meal_lock);
	ft_usleep(philo->infos->time_to_eat, philo->infos);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	log_action(philo, "is sleeping");
	ft_usleep(philo->infos->time_to_sleep, philo->infos);
	return (0);
}

int	philo_think(t_philo *philo)
{
	if (check_death(philo))
		return (1);
	log_action(philo, "is thinking");
	return (0);
}

void	check_one_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->infos->print_log);
	printf("%zu %d %s\n", curr_time_ms() - philo->infos->start_time,
		philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->infos->print_log);
	ft_usleep(philo->infos->time_to_die, philo->infos);
	pthread_mutex_unlock(philo->l_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	log_action(philo, "is thinking");
	if (philo->id % 2 == 0)
		ft_usleep(20, philo->infos);
	pthread_mutex_lock(&philo->infos->meal_lock);
	philo->last_meal_tm = curr_time_ms();
	pthread_mutex_unlock(&philo->infos->meal_lock);
	if (philo->infos->num_philos == 1)
		return (check_one_fork(philo), NULL);
	while (!check_death(philo))
	{
		if (philo_eat(philo))
			break ;
		if (philo_sleep(philo))
			break ;
		if (philo_think(philo))
			break ;
	}
	return (NULL);
}
