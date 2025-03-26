/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:13:29 by aharder           #+#    #+#             */
/*   Updated: 2025/03/26 16:40:10 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>

typedef struct s_philosophers
{
	pthread_t	thread_id;
	int		id;
	pthread_mutex_t	fork;
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

typedef struct s_data
{
	t_philosophers	*philosophers;
	t_params	params;
	int			actual_id;
}	t_data;

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

void	routine(t_data *data)
{
	t_philosophers	*table;
	pthread_t tid;

	tid = pthread_self();
	table = data->philosophers;
	while (data->actual_id == table->id)
	{
		table = table->next;
	}
	while (1)
	{
		if (table->id % 2 == 0)
		{
			pthread_mutex_lock(&table->fork);
			printf("Thread [%ld] took right fork", tid);
			pthread_mutex_lock(&table->previous->fork);
			printf("Thread [%ld] took left fork", tid);
		}
		else
		{
			pthread_mutex_lock(&table->previous->fork);
			printf("Thread [%ld] took left fork", tid);
			pthread_mutex_lock(&table->fork);
			printf("Thread [%ld] took right fork", tid);
		}
		table->time_ate++;
		usleep(data->params.time_to_eat);
		pthread_mutex_unlock(&table->fork);
		printf("Thread [%ld] drop right fork", tid);
		pthread_mutex_unlock(&table->previous->fork);
		printf("Thread [%ld] drop left fork", tid);
	}
}
void	init_philosophers(char *arg, t_philosophers *philosophers, t_params params)
{
	t_philosophers	*tmp;
	int	i;

	i = 0;
	while (i < ft_atoi(arg))
	{
		tmp = malloc(sizeof(t_philosophers));
		tmp->status = 0;
		tmp->time_ate = 0;
		gettimeofday(&tmp->last_meal, NULL);
		tmp->next = NULL;
		tmp->previous = NULL;
		if (philosophers == NULL)
			philosophers = tmp;
		else
		{
			tmp->next = philosophers;
			philosophers->previous = tmp;
			philosophers = tmp;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_params	params;
	pthread_t	*philosophers;
	int				num;
	int				i;

	i = 0;
	num = ft_atoi(argv[1]);
	philosophers = malloc((num + 1) * sizeof(pthread_t));
	while (i < num)
	{
		pthread_create(philosophers[i], NULL, routine, NULL);
		i++;
	}
	i = 0;
	while (i < num)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}
}
