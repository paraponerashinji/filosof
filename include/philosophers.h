/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:54 by aharder           #+#    #+#             */
/*   Updated: 2025/04/26 15:35:05 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>

typedef struct s_params
{
	unsigned int	number_of_philo;
	struct timeval	start_simulation;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_die;
	bool			limited_eating;
	unsigned int	number_to_eat;
}	t_params;

typedef struct s_philosophers
{
	pthread_t				philo_thread;
	pthread_mutex_t			fork;
	int						id;
	int						time_ate;
	struct timeval			last_meal;
	struct s_philosophers	*next;
	struct s_philosophers	*previous;
	t_params				simulation_params;
}	t_philosophers;