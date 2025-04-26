/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:50:50 by aharder           #+#    #+#             */
/*   Updated: 2025/04/26 15:31:44 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

t_params	init_param(int argc, char *argv[])
{
	t_params	params;

	params.number_of_philo = ft_atoi(argv[1]);
	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	gettimeofday(&params.start_simulation, NULL);
	if (argv[5])
	{
		params.limited_eating = 1;
		params.number_to_eat = ft_atoi(argv[5]);
	}
	else
		params.limited_eating = 0;
	return (params);
}

void	init_philo(t_philosophers *philo, int argc, char *argv[])
{
	t_params		config;
	t_philosophers	*tmp;
	int				i;

	config = init_param(argc, argv);
	while (i < config.number_of_philo)
	{
		tmp = malloc(sizeof(t_philosophers));
		tmp->id = i;
		tmp->last_meal = config.start_simulation;
		pthread_mutex_init(&tmp->fork, NULL);
		tmp->next = NULL;
		tmp->previous = NULL;
		tmp->simulation_params = config;
		if (!philo)
			philo = tmp;
		else
		{
			tmp->next = philo;
			philo->previous = tmp;
			philo = tmp;
		}
		i++;
	}
}