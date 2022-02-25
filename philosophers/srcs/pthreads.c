/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:48:21 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/25 15:42:12 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*cast_philo;

	cast_philo = (t_philo *)philo;
	cast_philo->when_die
		= cast_philo->start_time + cast_philo->info[TIME_TO_DIE];
	while (*(cast_philo->is_die) == FALSE)
	{
		mutex_prt_think(cast_philo->idx_of_philo, cast_philo->anounce);
		pthread_mutex_lock(&(cast_philo->forks[0]));
		mutex_prt_fork(cast_philo->idx_of_philo, cast_philo->anounce);
		pthread_mutex_lock(&(cast_philo->forks[1]));
		mutex_prt_fork(cast_philo->idx_of_philo, cast_philo->anounce);
		action_eat(philo);
		pthread_mutex_unlock(&(cast_philo->forks[1]));
		pthread_mutex_unlock(&(cast_philo->forks[0]));
		action_sleep(philo);
	}
	return (NULL);
}

void	*routine_zero(void *philo)
{
	t_philo	*cast_philo;

	cast_philo = (t_philo *)philo;
	cast_philo->when_die
		= cast_philo->start_time + cast_philo->info[TIME_TO_DIE];
	while (*(cast_philo->is_die) == FALSE)
	{
		mutex_prt_think(cast_philo->idx_of_philo, cast_philo->anounce);
		pthread_mutex_lock(&(cast_philo->forks[1]));
		mutex_prt_fork(cast_philo->idx_of_philo, cast_philo->anounce);
		pthread_mutex_lock(&(cast_philo->forks[0]));
		mutex_prt_fork(cast_philo->idx_of_philo, cast_philo->anounce);
		action_eat(philo);
		pthread_mutex_unlock(&(cast_philo->forks[0]));
		pthread_mutex_unlock(&(cast_philo->forks[1]));
		action_sleep(philo);
	}
	return (NULL);
}

int	creat_pthreads(t_philo *philos)
{
	int	idx;

	idx = 1;
	pthread_create(&philos[0].thread, NULL, routine_zero, &philos[0]);
	while (idx < philos->info[NUM_OF_PHILO])
	{
		pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]);
		++idx;
	}
	return (SUCCESS);
}

void	detach_pthreads(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->info[NUM_OF_PHILO])
		pthread_detach(philos[idx++].thread);
}
