/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:50 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 15:09:49 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_params	*init_param(int argc, char *argv[])
{
	t_params	*params;

	params = malloc(sizeof(t_params));
	(void)argc;
	params->number_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	params->simulation_end = 0;
	pthread_mutex_init(&params->simulation_state, NULL);
	gettimeofday(&params->start_simulation, NULL);
	if (argv[5])
	{
		params->limited_eating = 1;
		params->number_to_eat = ft_atoi(argv[5]);
	}
	else
		params->limited_eating = 0;
	return (params);
}

void	init_more(t_philo **tmp, t_params **config)
{
	(*tmp)->color = generate_random_color((*tmp)->id);
	(*tmp)->last_meal = (*config)->start_simulation;
	(*tmp)->time_ate = 0;
	pthread_mutex_init(&(*tmp)->fork, NULL);
	(*tmp)->next = NULL;
	(*tmp)->data = *config;
}

void	init_philo(t_philo **philo, t_params **config, int argc, char *argv[])
{
	t_philo	*tmp;
	t_philo	*last;
	int		i;

	*config = init_param(argc, argv);
	i = 0;
	last = NULL;
	while (i < (*config)->number_of_philo)
	{
		tmp = malloc(sizeof(t_philo));
		tmp->id = i;
		init_more(&tmp, config);
		tmp->previous = last;
		if (last)
			last->next = tmp;
		else
			*philo = tmp;
		last = tmp;
		i++;
	}
	if (last && *philo)
	{
		last->next = *philo;
		(*philo)->previous = last;
	}
}
