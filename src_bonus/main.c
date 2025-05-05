/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:02:42 by aharder           #+#    #+#             */
/*   Updated: 2025/05/05 13:17:36 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	main(int argc, char *argv[])
{
	t_params		params;
	int				i;

	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	init_philo(&params, argc, argv);
	i = 0;
	printf("Start at %ld\n", timeval_to_ms(params.start_simulation));
	create_philo_process(params);
	i = 0;
	while (i < params.number_of_philo)
	{
		//pthread_join(philosophers->philo_thread, NULL);
		i++;
	}
}