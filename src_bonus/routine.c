/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:37:06 by aharder           #+#    #+#             */
/*   Updated: 2025/05/07 11:29:46 by aharder          ###   ########.fr       */
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

void	thinking(t_params *philo, int id)
{
	struct timeval	t;

	sem_wait(philo->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d is thinking\n", philo->color, timeval_to_ms(t),id);
	sem_post(philo->simulation_state);
}

void	sleeping(t_params *philo, int id)
{
	struct timeval	t;

	sem_wait(philo->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d is sleeping\n", philo->color, timeval_to_ms(t), id);
	sem_post(philo->simulation_state);
	usleep(philo->time_to_sleep * 1000);
}

void	eating(t_params *philo, int id)
{
	struct timeval	t;

	grabfork(philo);
	sem_wait(philo->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s[%ld] %d has taken a fork\n", philo->color, timeval_to_ms(t), id);
	gettimeofday(&philo->last_meal, NULL);
	printf("%s[%ld] %d is eating\n", philo->color, timeval_to_ms(philo->last_meal), id);
	sem_post(philo->simulation_state);
	usleep(philo->time_to_eat * 1000);
	if (philo->number_to_eat != -1)
		sem_wait(philo->time_ate[id]);
	dropfork(philo);
}

void	end_simulation(t_params *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		if (i != philo->id)
			kill(philo->philo_pid[i], SIGQUIT);
		i++;
	}
	exit(0);
}

void	has_all_eaten(t_params *philo)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		sem_wait(philo->time_ate[i]);
		if (philo->number_to_eat != -1)
			philo->number_to_eat--;
		if (philo->number_to_eat == 0)
		{
			end_simulation(philo);
			break ;
		}
		i++;
	}
}

void	philo_lifeline(t_params *philo)
{
	struct timeval	t;
	long			current_time;
	long			last_meal;

	while (1)
	{
		sem_wait(philo->simulation_state);
		last_meal = timeval_to_ms(philo->last_meal);
		sem_post(philo->simulation_state);
		gettimeofday(&t, NULL);
		current_time = timeval_to_ms(t);
		if ((current_time - last_meal) >= philo->time_to_die)
		{
			sem_wait(philo->simulation_state);
			printf("%s%d is dead at %ld\n", philo->color, philo->id, current_time);
			printf("Final last meal: %ld\n", last_meal);
			printf("%s%d should died at %ld\n", philo->color, philo->id, last_meal + philo->time_to_die);
			end_simulation(philo);
			break ;
		}
		usleep(100);
	}
}

void	routine(t_params *philo, int id)
{
	
	philo->philo_pid[id] = fork();
	if (philo->philo_pid[id] == 0)
	{
		philo->id = id;
		pthread_create(&philo->philo_lifeline, NULL, (void *)philo_lifeline, philo);
		while (1)
		{
			eating(philo, id);
			sleeping(philo, id);
			thinking(philo, id);
		}
	}
	else
	{
		waitpid(philo->philo_pid[id]);
	}
}