/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:37:06 by aharder           #+#    #+#             */
/*   Updated: 2025/05/13 12:20:59 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	end_simulation(t_params *philo)
{
	(void)philo;
	exit(0);
}

void	print_philo(t_params *philo, char *msg)
{
	struct timeval	t;
	long			current_time;

	gettimeofday(&t, NULL);
	current_time = timeval_to_ms(t);
	sem_wait(philo->simulation_state);
	printf("%s[%ld] %d %s\n", philo->color[philo->id], current_time, philo->id, msg);
	sem_post(philo->simulation_state);
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
		if ((current_time - last_meal) >= philo->time_to_die && has_eaten_enough(philo, philo->id))
		{
			sem_wait(philo->simulation_state);
			printf("%s[%ld] %d is dead\n", philo->color[philo->id], current_time, philo->id);
			//sem_post(philo->simulation_state);
			end_simulation(philo);
			break ;
		}
		usleep(100);
	}
}

void	grabfork(t_params *philo)
{
	sem_wait(philo->table);
	sem_wait(philo->fork);
	print_philo(philo, "has taken a fork");
	sem_wait(philo->fork);
	print_philo(philo, "has taken a fork");
	sem_post(philo->table);
}

void	dropfork(t_params *philo)
{
	sem_post(philo->fork);
	sem_post(philo->fork);
}

void	thinking(t_params *philo, int id)
{
	(void)id;
	print_philo(philo, "is thinking");
}

void	sleeping(t_params *philo, int id)
{
	(void)id;
	print_philo(philo, "is sleeping");
	usleep(philo->time_to_sleep * 1000);
}

int	has_eaten_enough(t_params *philo, int id)
{
	int	r;

	r = 0;

	(void)id;
	pthread_mutex_lock(&philo->meal);
	if (philo->number_to_eat == -1)
		r = 1;
	if (philo->number_to_eat > 0)
		r = 1;
	pthread_mutex_unlock(&philo->meal);
	return (r);
}

void	eating(t_params *philo, int id)
{
	struct timeval	t;

	grabfork(philo);
	sem_wait(philo->simulation_state);
	gettimeofday(&t, NULL);
	gettimeofday(&philo->last_meal, NULL);
	sem_post(philo->simulation_state);
	print_philo(philo, "is eating");
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_lock(&philo->meal);
	if (philo->number_to_eat != -1)
		philo->number_to_eat--;
	pthread_mutex_unlock(&philo->meal);
	dropfork(philo);
	if (has_eaten_enough(philo, id) == 0)
		return ;
	gettimeofday(&t, NULL);
	print_philo(philo, "dropped forks");
}
/*
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
}*/

void	routine(t_params *philo, int id)
{
	philo->philo_pid[id] = fork();
	if (philo->philo_pid[id] == 0)
	{
		philo->id = id;
		pthread_create(&philo->philo_lifeline, NULL, (void *)philo_lifeline, philo);
		pthread_detach(philo->philo_lifeline);
		while (has_eaten_enough(philo, id))
		{
			eating(philo, id);
			sleeping(philo, id);
			thinking(philo, id);
		}
		//printf("%s[%ld] meal count: %d\n", philo->color[philo->id], timeval_to_ms(philo->last_meal), philo->number_to_eat);
		usleep(1000000);
		exit(0);
	}
}