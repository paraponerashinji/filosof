/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:26:37 by aharder           #+#    #+#             */
/*   Updated: 2025/05/02 18:58:16 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char *argv[])
{
	t_philo	*philosophers;
	t_params		*params;
	int				i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	philosophers = NULL;
	init_philo(&philosophers, &params, argc, argv);
	i = 0;
	printf("Start at %ld\n", timeval_to_ms(params->start_simulation));
	while (i < params->number_of_philo)
	{
		pthread_create(&philosophers->philo_thread, NULL, (void *)routine, philosophers);
		i++;
		philosophers = philosophers->next;
	}
	params->simulation_end = 0;
	philo_lifeline(philosophers);
	i = 0;
	while (i < params->number_of_philo)
	{
		//pthread_join(philosophers->philo_thread, NULL);
		i++;
		philosophers = philosophers->next;
	}
}