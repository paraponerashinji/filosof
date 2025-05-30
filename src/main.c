/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 23:26:37 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 15:10:58 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	free_philo(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		j;

	i = philo->data->number_of_philo;
	j = 0;
	while (j < i)
	{
		j++;
		tmp = philo;
		philo = philo->next;
		free(tmp->color);
		pthread_mutex_destroy(&tmp->fork);
		free(tmp);
	}
}

void	free_params(t_params *params)
{
	pthread_mutex_destroy(&params->simulation_state);
	free(params);
}

int	str_is_num(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (ft_isalnum(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	print_error(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s <number_of_philosophers>", argv[0]);
		printf(" <time_to_die> <time_to_eat> <time_to_sleep>");
		printf(" [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
	while (i < argc)
	{
		if (str_is_num(argv[i]) == 1)
		{
			printf("Usage: %s <number_of_philosophers>", argv[0]);
			printf(" <time_to_die> <time_to_eat> <time_to_sleep>");
			printf(" [number_of_times_each_philosopher_must_eat]\n");
			exit(1);
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_philo		*philosophers;
	t_params	*params;
	int			i;

	print_error(argc, argv);
	philosophers = NULL;
	init_philo(&philosophers, &params, argc, argv);
	i = 0;
	while (i < params->number_of_philo)
	{
		pthread_create(&philosophers->philo_thread, NULL,
			(void *)routine, philosophers);
		i++;
		philosophers = philosophers->next;
	}
	philo_lifeline(philosophers);
	i = 0;
	while (i < params->number_of_philo)
	{
		pthread_join(philosophers->philo_thread, NULL);
		i++;
		philosophers = philosophers->next;
	}
	free_philo(philosophers);
	free_params(params);
}
