/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:52 by aharder           #+#    #+#             */
/*   Updated: 2025/04/26 15:35:50 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	routine(t_philosophers *philo)
{
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(&philo->fork);
			printf("Thread [%ld] took right fork", tid);
			pthread_mutex_lock(&philo->previous->fork);
			printf("Thread [%ld] took left fork", tid);
		}
		else
		{
			pthread_mutex_lock(&philo->previous->fork);
			printf("Thread [%ld] took left fork", tid);
			pthread_mutex_lock(&philo->fork);
			printf("Thread [%ld] took right fork", tid);
		}
		philo->time_ate++;
		gettimeofday(&philo->last_meal, NULL);
		usleep(philo->simulation_params.time_to_eat);
		pthread_mutex_unlock(&philo->fork);
		printf("Thread [%ld] drop right fork", tid);
		pthread_mutex_unlock(&philo->previous->fork);
		printf("Thread [%ld] drop left fork", tid);
		usleep(philo->simulation_params.time_to_sleep);
	}
}