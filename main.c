/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:13:29 by aharder           #+#    #+#             */
/*   Updated: 2025/02/06 16:55:15 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

typedef struct s_philosophers
{
	pthread_t	thread_id;
	int		status;
	int		fork;
	int		time_ate;
	struct timeval		last_meal;
	struct s_philosophers	*next;
	struct s_philosophers	*previous;
}	t_philosophers;

typedef struct s_params
{
	unsigned int	time_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_sleep;
	unsigned int	number_to_eat;
}	t_params;

t_params	init_parameters(int argc, char *argv[])
{
	t_params	params;

	params.time_to_die = ft_atoi(argv[2]);
	params.time_to_eat = ft_atoi(argv[3]);
	params.time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		params.number_to_eat = ft_atoi(argv[5]);
	else
		params.number_to_eat = NULL;
	return (params);
}
int	main(int argc, char *argv[])
{
	t_params	params;

	check_args(argc, argv);
	init_philo_table(argv[1]);
	params = init_parameters(argc, argv);
	launch_simulation(philosophers, condition);
}
