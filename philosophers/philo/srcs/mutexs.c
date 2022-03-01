/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:47:26 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/01 15:37:44 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	destroy_mutexs(t_philo *philos)
{
	int	idx;

	idx = 0;
	pthread_mutex_destroy(philos->anounce);
	while (idx < philos->info[NUM_OF_PHILO])
	{
		pthread_mutex_destroy(philos[idx].restriction);
		pthread_mutex_destroy(philos[idx].eat);
		pthread_mutex_destroy(philos[idx++].forks[0]);
	}
}
