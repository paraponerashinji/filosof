/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:40:54 by aharder           #+#    #+#             */
/*   Updated: 2025/05/09 15:21:50 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
//#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define UNLOCK 1
#define LOCK 0

typedef struct s_philo
{
	int				id;
	unsigned int	time_ate;
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
	struct timeval	start_simulation;
	pthread_mutex_t	simulation_state;
}	t_params;

typedef struct s_randomcolor
{
	char			*color_code;
	int				red;
	int				green;
	int				blue;
	char			*red_str;
	char			*green_str;
	char			*blue_str;
	long			seed;
	struct timeval	t;
}	t_randomcolor;

void	routine(t_philo *philo);
void	init_philo(t_philo **philo, t_params **config, int argc, char *argv[]);
long	timeval_to_ms(struct timeval t);
char	*generate_random_color(int id);
void	philo_lifeline(void *arg);
void	print_philo(t_philo *philo, char *message);
int		simulation_on(t_philo *philo);
void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
int		has_all_philos_ate(t_philo *philo);
char	*ft_strjoin(char *dest, char *src);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strdup(char *src);
int		ft_isalnum(char c);
int		ft_strlen(const char *str);