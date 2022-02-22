/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:47:26 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/22 12:47:28 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

pthread_mutex_t	*init_mutexs(const int parsed_input[5])
{
	int				idx;
	pthread_mutex_t	*result;

	idx = 0;
	result = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * parsed_input[NUM_OF_PHILO]);
	if (result == NULL)
	{
		hdl_syscall("malloc");
		return (NULL);
	}
	while (idx < parsed_input[NUM_OF_PHILO])
	{
		if (pthread_mutex_init(&result[idx], NULL) != SUCCESS)
		{
			hdl_syscall("pthread_mutex_init");
			while (idx > 0)
				pthread_mutex_destroy(&result[--idx]);
			free(result);
			return (NULL);
		}
		++idx;
	}
	return (result);
}

void	destroy_mutexs(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->info[NUM_OF_PHILO])
		pthread_mutex_destroy(&philos[idx++].forks[0]);
}
