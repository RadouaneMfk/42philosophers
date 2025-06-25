/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmouafik <rmouafik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:02:21 by rmouafik          #+#    #+#             */
/*   Updated: 2025/05/18 09:58:19 by rmouafik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	unsigned long		result;
	int					i;

	result = 0;
	i = 0;
	while ((str[i] == ' ') || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 2147483647)
			return (-1);
	}
	return (result);
}

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') 
			|| str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
			i++;
		else
			return (1);
	}
	return (0);
}

size_t	curr_time_ms(void)
{
	struct timeval	va;

	gettimeofday(&va, NULL);
	return (va.tv_sec * 1000LL + va.tv_usec / 1000);
}

int	ft_get(int *value, pthread_mutex_t *lock)
{
	int	res;

	pthread_mutex_lock(lock);
	res = *value;
	pthread_mutex_unlock(lock);
	return (res);
}

void	log_action(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->infos->print_log);
	if (!ft_get(&philo->infos->dead, &philo->infos->death_lock))
	{
		printf("%zu %d %s\n", 
			curr_time_ms() - philo->infos->start_time, philo->id, action);
	}
	pthread_mutex_unlock(&philo->infos->print_log);
}
