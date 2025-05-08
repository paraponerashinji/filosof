/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aharder <aharder@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:44:23 by aharder           #+#    #+#             */
/*   Updated: 2025/05/08 22:47:06 by aharder          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	print_philo(t_philo *philo, char *message)
{
	struct timeval	t;

	if (simulation_on(philo) == 0)
	{
		gettimeofday(&t, NULL);
		printf("%s%ld %d %s\n", philo->color, timeval_to_ms(t),
			philo->id + 1, message);
	}
}