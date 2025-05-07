/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:52 by aharder           #+#    #+#             */
/*   Updated: 2025/05/08 00:12:49 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	has_all_philos_ate(t_philo *philo)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (philo->data->limited_eating == 0)
		return (0);
	//pthread_mutex_lock(&philo->data->simulation_state);
	while (i < philo->data->number_of_philo)
	{
		if (philo->time_ate >= philo->data->number_to_eat)
			count++;
		i++;
		philo = philo->next;
	}
	//pthread_mutex_unlock(&philo->data->simulation_state);
	if (count == philo->data->number_of_philo)
		return (1);
	return (0);
}

void	customsleep(long start, long time)
{
	struct timeval	t;
	long			current_time;
	
	(void)start;
	while (1)
	{
		gettimeofday(&t, NULL);
		current_time = timeval_to_ms(t);
		if (current_time >= time)
			break ;
		usleep(500);
	}
}

void	grapfork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		//usleep(500);
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
	printf("%s%ld %d has taken a fork\n", philo->color, timeval_to_ms(t), philo->id);
	gettimeofday(&t, NULL);
	printf("%s%ld %d has taken a fork\n", philo->color, timeval_to_ms(t), philo->id);
	pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&philo->last_meal, NULL);
	printf("%s%ld %d is eating\n", philo->color, timeval_to_ms(philo->last_meal),philo->id);
	//printf("%s[%ld] %d Time ate: %d\n", philo->color, timeval_to_ms(t), philo->id, philo->time_ate + 1);
	philo->time_ate++;
	pthread_mutex_unlock(&philo->data->simulation_state);
	/*if (has_all_philos_ate(philo) == 1)
	{
		dropfork(philo);
		return ;
	}*/
	customsleep(timeval_to_ms(t), timeval_to_ms(t) + philo->data->time_to_eat);
	dropfork(philo);
	gettimeofday(&t, NULL);
	//printf("%s[%ld] %d dropped forks\n", philo->color, timeval_to_ms(t), philo->id);
}
void	sleeping(t_philo *philo)
{
	struct timeval	t;
	
	pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s%ld %d is sleeping\n", philo->color, timeval_to_ms(t), philo->id);
	pthread_mutex_unlock(&philo->data->simulation_state);
	customsleep(timeval_to_ms(t), timeval_to_ms(t) + philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	struct timeval	t;

	//pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&t, NULL);
	printf("%s%ld %d is thinking\n", philo->color, timeval_to_ms(t), philo->id);
	//pthread_mutex_unlock(&philo->data->simulation_state);
}

void	routine(t_philo *philo)
{
	//struct timeval	start;
	//struct timeval	end;

	pthread_mutex_lock(&philo->data->simulation_state);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->data->simulation_state);
	while (1)
	{
		//gettimeofday(&start, NULL);
		eating(philo);
		if (philo->data->limited_eating != 0)
		{
			//printf("%s[%ld] %d time ate: %d\n", philo->color, timeval_to_ms(philo->last_meal), philo->id, philo->time_ate);
			if (philo->time_ate >= philo->data->number_to_eat)
			{
				break ;
			}
		}
		sleeping(philo);
		thinking(philo);
	}
}

void	end_simulation(t_philo *philo)
{
    int		i;

    i = 0;
    while (i < philo->data->number_of_philo)
    {
        pthread_detach(philo->philo_thread);
        //pthread_mutex_destroy(&philo->fork);
        i++;
        philo = philo->next;
    }
	//exit(0);
}

void	destroy_all_other_lifeline(t_philo *philo)
{
	int		i;
	int		id;

	id = philo->id;
	i = 0;
	while (id != philo->id)
	{
		pthread_detach(philo->philo_lifeline);
		pthread_mutex_lock(&philo->fork);
		i++;
		philo = philo->next;
	}
	philo->data->simulation_end = 1;
}

void	lifeline_routine(t_philo *philo)
{
	struct timeval	t;
	long			current_time;
	long			last_meal;

	pthread_mutex_lock(&philo->data->simulation_state);
	while (has_all_philos_ate(philo) == 0)
	{
		if (philo->data->simulation_end == 1)
		{
			pthread_mutex_unlock(&philo->data->simulation_state);
			break ;
		}
		last_meal = timeval_to_ms(philo->last_meal);
		pthread_mutex_unlock(&philo->data->simulation_state);
		gettimeofday(&t, NULL);
		current_time = timeval_to_ms(t);
		if ((current_time - last_meal) >= philo->data->time_to_die)
		{
			//pthread_mutex_lock(&philo->data->simulation_state);
			/*
			if (philo->time_ate >= philo->data->number_to_eat && has_all_philos_ate(philo) == 1)
			{
				pthread_mutex_unlock(&philo->data->simulation_state);
				continue;
			}*/
			pthread_mutex_lock(&philo->data->simulation_state);
			if (has_all_philos_ate(philo) == 0)
			{
				printf("%s%ld %d died\n", philo->color, timeval_to_ms(t), philo->id);
				printf("%s%d is dead at %ld\n", philo->color, philo->id, current_time);
				printf("Final last meal: %ld\n", last_meal);
				printf("Count: %d\n", philo->time_ate);
				printf("%s%d should died at %ld\n", philo->color, philo->id, last_meal + philo->data->time_to_die);
			}
			end_simulation(philo);
			destroy_all_other_lifeline(philo);
			pthread_mutex_unlock(&philo->data->simulation_state);
			break ;
		}
		usleep(100);
		pthread_mutex_lock(&philo->data->simulation_state);
	}
	//pthread_mutex_destroy(&philo->data->simulation_state);
}

void	philo_lifeline(void *arg)
{
	t_philo	*table;
	int		i;

	i = 0;
	table = (t_philo *)arg;
	while (i < table->data->number_of_philo)
	{
		pthread_create(&table->philo_lifeline, NULL, (void *)lifeline_routine, table);
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