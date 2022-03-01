/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:48:21 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/28 00:18:11 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

void	*die_check(void *in)
{
	t_philo	*philo;

	philo = (t_philo *)in;
	while (1)
	{
		sem_wait(philo->die_check);
		if (get_time(FALSE) > philo->when_die)
		{
			sem_prt_die(philo->idx_of_philo, philo->anounce);
			sem_post(philo->die);
			break ;
		}
		usleep(100);
		sem_post(philo->die_check);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	philo->when_die = get_time(TRUE) + philo->info[TIME_TO_DIE];
	pthread_create(philo->thread, NULL, die_check, philo);
	while (1)
	{
		sem_prt_think(philo->idx_of_philo, philo->anounce);
		sem_wait(philo->restriction);
		sem_wait(philo->forks);
		sem_post(philo->restriction);
		sem_prt_fork(philo->idx_of_philo, philo->anounce);
		sem_wait(philo->forks);
		sem_prt_fork(philo->idx_of_philo, philo->anounce);
		action_eat(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		action_sleep(philo);
	}
}
