/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:48:21 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/23 18:06:24 by gyeon            ###   ########.fr       */
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
			printf("%llu %d died\n", get_elapsed_time(), philo->idx_of_philo);
			sem_post(philo->die);
			break;
		}
		usleep(5000);
		sem_post(philo->die_check);
	}
	return (NULL);
}



int	routine(t_philo *philo)
{
	philo->when_die = get_time(TRUE) + philo->info[TIME_TO_DIE];
	pthread_create(philo->thread, NULL, die_check, philo);
	while (1)
	{
		printf("%llu %d is thinking\n", get_elapsed_time(),
			   philo->idx_of_philo);
		sem_wait(philo->forks);
		printf("%llu %d is has taken a fork\n",
			   get_elapsed_time(), philo->idx_of_philo);
		sem_wait(philo->forks);
		printf("%llu %d is has taken a fork\n",
			   get_elapsed_time(), philo->idx_of_philo);
		action_eat(philo);
		sem_post(philo->forks);
		sem_post(philo->forks);
		action_sleep(philo);
	}
	return (FAILURE);
}

// int	creat_pthreads(t_philo *philos)
// {
// 	int	idx;

// 	idx = 0;
// 	while (idx < philos->info[NUM_OF_PHILO])
// 	{
// 		pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]);
// 		++idx;
// 	}
// 	return (SUCCESS);
// }

// void	join_pthreads(t_philo *philos)
// {
// 	int	idx;

// 	idx = 0;
// 	while (idx < philos->info[NUM_OF_PHILO])
// 		pthread_join(philos[idx++].thread, NULL);
// }
