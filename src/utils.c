/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:31:42 by aharder           #+#    #+#             */
/*   Updated: 2025/05/07 11:52:08 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

long	timeval_to_ms(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

typedef struct s_trylock
{
	pthread_mutex_t	*mutex;
	int			i;
}	t_trylock;

void	*trylock(t_trylock *trylock)
{
	pthread_mutex_lock(trylock->mutex);
	trylock->i = 1;
	pthread_mutex_unlock(trylock->mutex);
	return (NULL);
}

int	ft_trylock(pthread_mutex_t *mutex)
{
	pthread_t	thread_id;
	t_trylock	strylock;

	strylock.mutex = mutex;
	strylock.i = 0;
	pthread_create(&thread_id, NULL, (void *)trylock, &strylock);
	usleep(100000);
	pthread_detach(thread_id);
	if (strylock.i == 1)
		return (1);
	return (0);
}

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