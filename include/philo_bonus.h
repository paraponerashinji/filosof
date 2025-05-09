/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:03:17 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 15:58:56 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"
#include <signal.h>


typedef struct s_params
{
	int				id;
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	int	number_to_eat;
	int				number_of_philo;
	pthread_mutex_t	meal;
	struct timeval	last_meal;
	char			**color;
	pid_t			*philo_pid;
	pthread_mutex_t	death;
	pthread_t		philo_lifeline;
	struct timeval	start_simulation;
	sem_t			*fork;
	sem_t			*simulation_state;
}	t_params;

void	init_philo(t_params *params, int argc, char *argv[]);
long	timeval_to_ms(struct timeval t);
void	create_philo_process(t_params *params);
void	routine(t_params *philo, int id);
char	*ft_strjoin(char *dest, char *src);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(char *src);
int		ft_isalnum(char c);
int		ft_strlen(const char *str);