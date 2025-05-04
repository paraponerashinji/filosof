/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:31:02 by aharder           #+#    #+#             */
/*   Updated: 2025/05/04 23:40:09 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

char	*generate_random_color(int id)
{
	char	*color_code;
	int		red;
	int		green;
	int		blue;
	char	*red_str;
	char	*green_str;
	char	*blue_str;

	id++;
	color_code = malloc(24 * sizeof(char));
	red = (id * 53) % 256;
	green = (id * 97) % 256;
	blue = (id * 193) % 256;
	red_str = ft_itoa(red);
	green_str = ft_itoa(green);
	blue_str = ft_itoa(blue);
	color_code = ft_multistrjoin(7, "\033[38;2;", red_str, ";", green_str, ";", blue_str, "m");
	free(red_str);
	free(green_str);
	free(blue_str);
	return (color_code);
}

void	init_color(t_params *params)
{
	int		i;

	i = 0;
	while (i < params->number_of_philo)
	{
		params->color[i] = generate_random_color(i);
		i++;
	}
}

void	start_philo(t_params *params, int i)
{
	params->philo_pid[i] = fork();
	if (params->philo_pid[i] == 0)
	{
		while (1)
		{
			pthread_create(&params->philo_lifeline[i], NULL, (void *)philo_lifeline, &params->philo_pid[i]);
			struct timeval	t;
			eating(params, i);
			sleeping(params, i);
			thinking(params, i);
		}
	}

}

void	create_philo_process(t_params *params)
{
	int		i;

	i = 0;
	while (i < params->number_of_philo)
	{
		routine(params, i);
		i++;
	}
}

void	init_philo(t_params *params, int argc, char *argv[])
{
	int		i;

	params->number_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->number_to_eat = ft_atoi(argv[5]);
	else
		params->number_to_eat = -1;
	params->time_ate = sem_open("/time_ate", O_CREAT | O_EXCL, 0644, params->number_of_philo);
	params->color = malloc(sizeof(char *) * params->number_of_philo);
	init_color(params);
	params->philo_pid = malloc(sizeof(pid_t) * params->number_of_philo);
	params->fork = sem_open("/forks", O_CREAT | O_EXCL, 0644, params->number_of_philo);
	params->simulation_state = sem_open("/simulation_state", O_CREAT | O_EXCL, 0644, 1);
	pthread_mutex_init(&params->death, NULL);
	gettimeofday(&params->start_simulation, NULL);
	gettimeofday(&params->last_meal, NULL);
}