/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:31:42 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 14:52:12 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	thinking(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_philo(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	print_philo(philo, "is sleeping");
	usleep(philo->data->time_to_sleep * 1000);
}

long	timeval_to_ms(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}
/*
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
}*/

char	*generate_random_color(int id)
{
	t_randomcolor	s;
	char			*buffer;

	id += 1;
	s.red = (id * 53) % 256;
	s.green = (id * 97) % 256;
	s.blue = (id * 193) % 256;
	s.red_str = ft_itoa(s.red);
	s.green_str = ft_itoa(s.green);
	s.blue_str = ft_itoa(s.blue);
	buffer = ft_strjoin("\033[38;2;", s.red_str);
	s.color_code = ft_strjoin(buffer, ";");
	free(buffer);
	buffer = ft_strjoin(s.color_code, s.green_str);
	free(s.color_code);
	s.color_code = ft_strjoin(buffer, ";");
	free(buffer);
	buffer = ft_strjoin(s.color_code, s.blue_str);
	free(s.color_code);
	s.color_code = ft_strjoin(buffer, "m");
	free(buffer);
	free(s.red_str);
	free(s.green_str);
	free(s.blue_str);
	return (s.color_code);
}
