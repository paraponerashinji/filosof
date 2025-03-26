/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:13:29 by aharder           #+#    #+#             */
/*   Updated: 2025/03/27 00:12:09 by aharder          ###   ########.fr       */
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
		gettimeofday(&table->last_meal, NULL);
		usleep(data->params.time_to_eat);
		pthread_mutex_unlock(&table->fork);
		printf("Thread [%ld] drop right fork", tid);
		pthread_mutex_unlock(&table->previous->fork);
		printf("Thread [%ld] drop left fork", tid);
		usleep(data->params.time_to_sleep);
	}
}

long	timeval_to_ms(struct timeval t)
{
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	check_if_alive(t_data *data)
{
	t_philosophers	*table;
	long			last_meal;
	long			current_time;
	struct timeval	t;
	
	table = data->philosophers;
	while (1)
	{
		last_meal = timeval_to_ms(table->last_meal);
		gettimeofday(&t, NULL);
		current_time = timeval_to_ms(t);
		if ((current_time - last_meal) >= data->params.time_to_die)
		{
			destroy_all_thread(table);
			break;
		}
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
		tmp->id = i;
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
