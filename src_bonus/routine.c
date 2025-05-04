/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:37:06 by aharder           #+#    #+#             */
/*   Updated: 2025/05/04 23:43:22 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	grabfork(t_params *philo)
{
	sem_wait(philo->fork);
	sem_wait(philo->fork);
}

void	dropfork(t_params *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	thinking(t_philo *philo, int id)
{
	struct timeval	t;

	sem_wait(philo->data->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d is thinking\n", philo->color, timeval_to_ms(t), philo->id);
	sem_post(philo->data->simulation_state);
}

void	sleeping(t_params *philo, int id)
{
	struct timeval	t;

	sem_wait(philo->data->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d is sleeping\n", philo->color, timeval_to_ms(t), philo->id);
	sem_post(philo->data->simulation_state);
	usleep(philo->data->time_to_sleep * 1000);
}

void	eating(t_params *philo, int id)
{
	struct timeval	t;

	grabfork(philo);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d has taken a fork\n", philo->color, timeval_to_ms(t), id);
	gettimeofday(&philo->last_meal, NULL);
	printf("%s[%ld] %d is eating\n", philo->color, timeval_to_ms(philo->last_meal), id);
	usleep(philo->time_to_eat * 1000);
	sem_post(philo->time_ate);
	dropfork(philo);
}

void	routine(t_params *philo, int id)
{
	
	philo->philo_pid[id] = fork();
	if (philo->philo_pid[id] == 0)
	{
		pthread_create(&philo->philo_lifeline, NULL, (void *)philo_lifeline, philo);
		while (1)
		{
			eating(philo, id);
			sleeping(philo, id);
			thinking(philo, id);
		}
	}
}