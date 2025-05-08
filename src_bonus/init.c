/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 22:31:02 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 00:04:55 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

char	*ft_multistrjoin(int count, ...)
{
	va_list		args;
	char		*result;
	char		*buffer1;
	int			i;

	va_start(args, count);
	i = 0;
	result = malloc(1);
	result[0] = '\0';
	while (i < count)
	{
		buffer1 = result;
		result = ft_strjoin(buffer1, va_arg(args, char *));
		free(buffer1);
		i++;
	}
	va_end(args);

	return (result);
}

char	*generate_random_color(int id)
{
	char	*color_code;
	int		red;
	int		green;
	int		blue;
	char	*red_str;
	char	*green_str;
	char	*blue_str;
	long	seed;
	struct timeval	t;

	gettimeofday(&t, NULL);
	seed = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	id += seed % 1000;
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

void	init_time_ate(t_params *params)
{
	int		i;
	char	*name;
	char	*id;

	i = 0;
	while (i < params->number_of_philo)
	{
		id = ft_itoa(i);
		name = ft_strjoin("/time_ate", id);
		sem_unlink(name);
		params->time_ate[i] = sem_open(name, O_CREAT | O_EXCL, 0644, params->number_to_eat);
		free(id);
		free(name);
		i++;
	}
}

void	init_philo(t_params *params, int argc, char *argv[])
{
	params->number_of_philo = ft_atoi(argv[1]);
	params->time_to_die = ft_atoi(argv[2]);
	params->time_to_eat = ft_atoi(argv[3]);
	params->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		params->number_to_eat = ft_atoi(argv[5]);
	else
		params->number_to_eat = -1;
	params->time_ate = malloc(sizeof(sem_t *) * params->number_of_philo);
	init_time_ate(params);
	params->color = malloc(sizeof(char *) * params->number_of_philo);
	init_color(params);
	params->philo_pid = malloc(sizeof(pid_t) * params->number_of_philo);
	sem_unlink("/forks");
	params->fork = sem_open("/forks", O_CREAT | O_EXCL, 0644, params->number_of_philo);
if (params->fork == SEM_FAILED)
{
    perror("sem_open failed for forks");
    exit(EXIT_FAILURE);
}
	sem_unlink("/simulation_state");
params->simulation_state = sem_open("/simulation_state", O_CREAT | O_EXCL, 0644, 1);
if (params->simulation_state == SEM_FAILED)
{
    perror("sem_open failed for simulation_state");
    exit(EXIT_FAILURE);
}
	pthread_mutex_init(&params->death, NULL);
	gettimeofday(&params->start_simulation, NULL);
	gettimeofday(&params->last_meal, NULL);
}