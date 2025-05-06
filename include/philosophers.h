/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:54 by aharder           #+#    #+#             */
/*   Updated: 2025/05/06 23:16:26 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
#include "../libft/libft.h"
#include <stdio.h>

#define UNLOCK 1
#define LOCK 0

typedef struct s_philo
{
	int				id;
	unsigned int				time_ate;
	char			*color;
	struct timeval	last_meal;
	pthread_t		philo_thread;
	pthread_t		philo_lifeline;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*previous;
	struct s_params	*data;
}	t_philo;

typedef struct s_params
{
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	limited_eating;
	unsigned int	number_to_eat;
	int				number_of_philo;
	int				simulation_end;
	struct timeval			start_simulation;
	pthread_mutex_t	simulation_state;
}	t_params;

void	routine(t_philo *philo);
void	init_philo(t_philo **philo, t_params **config, int argc, char *argv[]);
long	timeval_to_ms(struct timeval t);
char	*generate_random_color(int id);
void	philo_lifeline(void *arg);