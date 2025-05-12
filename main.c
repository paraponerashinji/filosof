/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:13:29 by aharder           #+#    #+#             */
/*   Updated: 2025/04/27 23:04:37 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/time.h>
/*
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
}*/

#include "stdio.h"
#include <stdlib.h>

typedef struct s_philosopher
{
    int		id;
    char	*color;
}	t_philosopher;

#include <stdio.h>
#include <stdlib.h>

char	*generate_random_color(int id)
{
    char	*color_code;
    int		red;
    int		green;
    int		blue;

    // Alloue de la mémoire pour stocker le code couleur
    color_code = malloc(24 * sizeof(char));
    if (!color_code)
    {
        fprintf(stderr, "Error: Failed to allocate memory for color\n");
        return ("\033[0m"); // Retourne une couleur par défaut
    }

    // Génère des valeurs RGB pseudo-aléatoires basées sur l'ID
    red = (id * 53) % 256;
    green = (id * 97) % 256;
    blue = (id * 193) % 256;

    // Formate le code couleur ANSI
    snprintf(color_code, 24, "\033[38;2;%d;%d;%dm", red, green, blue);

    return (color_code);
}


int	main(int argc, char *argv[])
{
    int				num_philosophers;
    t_philosopher	*philosophers;
    int				i;

    if (argc != 2)
    {
        printf("Usage: %s <number_of_philosophers>\n", argv[0]);
        return (1);
    }

    // Récupère le nombre de philosophes
    num_philosophers = atoi(argv[1]);
    if (num_philosophers <= 0)
    {
        printf("Error: number_of_philosophers must be greater than 0\n");
        return (1);
    }

    // Alloue de la mémoire pour les philosophes
    philosophers = malloc(sizeof(t_philosopher) * num_philosophers);
    if (!philosophers)
    {
        perror("Failed to allocate memory for philosophers");
        return (1);
    }

    // Initialise les philosophes avec des couleurs aléatoires
    for (i = 0; i < num_philosophers; i++)
    {
        philosophers[i].id = i;
        philosophers[i].color = generate_random_color(i);
    }

    // Affiche les philosophes avec leurs couleurs
    for (i = 0; i < num_philosophers; i++)
    {
        printf("%sPhilosopher %d\033[0m\n", philosophers[i].color, philosophers[i].id);
    }

    // Libère la mémoire
    free(philosophers);

    return (0);
}
