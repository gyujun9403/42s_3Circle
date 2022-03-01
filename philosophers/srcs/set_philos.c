/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 00:23:55 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/28 19:13:55 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

/*
**					   left / right
** thread[0]	: mutex[0]	/ mutex[1]
** thread[1]	: mutex[1]	/ mutex[2]
** thread[2]	: mutex[2]	/ mutex[3]
** thread[n-1]	: mutex[n-1] / mutex[0]
*/
void	init_philos(t_philo *philos, pthread_t *threads,
	 pthread_mutex_t *mutexs, const int *parsed_input)
{
	int		idx;

	idx = 0;
	pthread_mutex_init(philos->anounce, NULL);
	*(philos->is_die) = FALSE;
	while (idx < parsed_input[NUM_OF_PHILO])
	{
		philos[idx].idx_of_philo = idx;
		philos[idx].forks[0] = mutexs[idx];
		if (idx + 1 == parsed_input[NUM_OF_PHILO])
			philos[idx].forks[1] = mutexs[0];
		else
			philos[idx].forks[1] = mutexs[idx + 1];
		philos[idx].info = (int *)parsed_input;
		philos[idx].thread = threads[idx];
		philos[idx].when_die = get_time(TRUE) + philos[idx].info[TIME_TO_DIE];
		philos[idx].is_die = philos->is_die;
		philos[idx].cnt_eat = 0;
		philos[idx].start_time = philos->start_time;
		philos[idx].anounce = philos->anounce;
		++idx;
	}
}

int	set_philos(t_philo *philos, const int parsed_input[5])
{
	pthread_t		*threads;
	pthread_mutex_t	*mutexs;

	mutexs = init_mutexs(parsed_input);
	if (mutexs == NULL)
		return (FALSE);
	else
	{
		philos->is_die = (int *)malloc(sizeof(int) * 1);
		philos->anounce = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		threads = (pthread_t *)
			malloc(sizeof(pthread_t) * parsed_input[NUM_OF_PHILO]);
		if (philos->is_die == NULL
			|| philos->anounce == NULL || threads == NULL)
			return (hdl_syscall("malloc"));
	}
	init_philos(philos, threads, mutexs, parsed_input);
	free(mutexs);
	free(threads);
	return (SUCCESS);
}

void	free_philos(t_philo *philos)
{
	free(philos->anounce);
	free(philos->is_die);
	free(philos);
}
