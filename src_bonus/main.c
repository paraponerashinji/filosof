/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:02:42 by aharder           #+#    #+#             */
/*   Updated: 2025/05/12 00:02:05 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long	timeval_to_ms(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	init_params(t_params *params, int argc, char *argv[])
{
	params->number_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->number_to_eat = ft_atoi(argv[5]);
	else
		params->number_to_eat = -1;
	params->philo_pid = NULL;
	params->color = NULL;
}

int	check_params(t_params *params, int argc)
{
	if (params->number_of_philo <= 0 || params->time_to_die <= 0
		|| params->time_to_eat <= 0 || params->time_to_sleep <= 0)
	{
		return (1);
	}
	if (argc == 6 && params->number_to_eat <= 0)
		return (1);
	return (0);
}

int	check_args(int argc, char *argv[])
{
	int	i;
	int	j;
	t_params	params;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isalnum(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	init_params(&params, argc, argv);
	if (check_params(&params, argc) == 1)
		return (1);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_params		params;
	int				i;

	if (check_args(argc, argv) == 1)
	{
		printf("Usage: %s <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n", argv[0]);
		return (1);
	}
	init_philo(&params, argc, argv);
	i = 0;
	printf("Start at %ld\n", timeval_to_ms(params.start_simulation));
	create_philo_process(&params);
	i = 0;
	while (i < params.number_of_philo)
	{
		//pthread_join(philosophers->philo_thread, NULL);
		i++;
	}
}