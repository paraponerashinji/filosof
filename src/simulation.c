/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:52 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 14:41:29 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->data->simulation_state);
	if (philo->data->number_of_philo == 1)
		return ;
	while (simulation_on(philo) == 0)
	{
		eating(philo);
		if (philo->data->limited_eating != 0)
		{
			if (philo->time_ate >= philo->data->number_to_eat)
				break ;
		}
		sleeping(philo);
		thinking(philo);
	}
}

void	end_simulation(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->number_of_philo)
	{
		i++;
		philo = philo->next;
	}
}

void	destroy_all_other_lifeline(t_philo *philo)
{
	int		i;
	int		id;

	id = philo->id;
	i = 0;
	pthread_mutex_lock(&philo->data->simulation_state);
	while (id != philo->id)
	{
		pthread_detach(philo->philo_lifeline);
		i++;
		philo = philo->next;
	}
	philo->data->simulation_end = 1;
	pthread_mutex_unlock(&philo->data->simulation_state);
}

void	lifeline_routine(t_philo *philo)
{
	struct timeval	t;
	long			current_time;
	long			last_meal;

	while (has_all_philos_ate(philo) == 0)
	{
		if (simulation_on(philo) == 1)
			break ;
		pthread_mutex_lock(&philo->data->simulation_state);
		last_meal = timeval_to_ms(philo->last_meal);
		pthread_mutex_unlock(&philo->data->simulation_state);
		gettimeofday(&t, NULL);
		current_time = timeval_to_ms(t);
		if ((current_time - last_meal) >= philo->data->time_to_die)
		{
			if (has_all_philos_ate(philo) == 0)
				print_philo(philo, "is dead");
			end_simulation(philo);
			destroy_all_other_lifeline(philo);
			break ;
		}
		usleep(100);
	}
}

void	philo_lifeline(void *arg)
{
	t_philo	*table;
	int		i;

	i = 0;
	table = (t_philo *)arg;
	while (i < table->data->number_of_philo)
	{
		pthread_create(&table->philo_lifeline, NULL,
			(void *)lifeline_routine, table);
		table = table->next;
		i++;
	}
	i = 0;
	while (i < table->data->number_of_philo)
	{
		pthread_join(table->philo_lifeline, NULL);
		i++;
		table = table->next;
	}
}
