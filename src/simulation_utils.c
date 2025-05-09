/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 14:36:47 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 14:39:05 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	simulation_on(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simulation_state);
	if (philo->data->simulation_end == 1)
	{
		pthread_mutex_unlock(&philo->data->simulation_state);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->simulation_state);
	return (0);
}

int	has_all_philos_ate(t_philo *philo)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (philo->data->limited_eating == 0)
		return (0);
	pthread_mutex_lock(&philo->data->simulation_state);
	while (i < philo->data->number_of_philo)
	{
		if (philo->time_ate >= philo->data->number_to_eat)
			count++;
		i++;
		philo = philo->next;
	}
	pthread_mutex_unlock(&philo->data->simulation_state);
	if (count == philo->data->number_of_philo)
		return (1);
	return (0);
}

void	grapfork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->fork);
		pthread_mutex_lock(&philo->previous->fork);
	}
	else
	{
		pthread_mutex_lock(&philo->previous->fork);
		pthread_mutex_lock(&philo->fork);
	}
}

void	dropfork(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->previous->fork);
}

void	eating(t_philo *philo)
{
	struct timeval	t;

	grapfork(philo);
	gettimeofday(&t, NULL);
	print_philo(philo, "has taken a fork");
	print_philo(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&philo->last_meal, NULL);
	philo->time_ate++;
	pthread_mutex_unlock(&philo->data->simulation_state);
	print_philo(philo, "is eating");
	if (has_all_philos_ate(philo) == 1)
	{
		dropfork(philo);
		return ;
	}
	usleep(philo->data->time_to_eat * 1000);
	dropfork(philo);
	print_philo(philo, "dropped forks");
	gettimeofday(&t, NULL);
}
