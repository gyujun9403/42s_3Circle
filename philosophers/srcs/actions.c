/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:47:47 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/21 20:34:33 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	action_eat(t_philo *philo)
{
	printf("%llu %d is eating\n",
		   get_time() - philo->start_time, philo->idx_of_philo);
	philo_msleep(philo->info[TIME_TO_EAT], philo);
	philo->when_die = get_time() + philo->info[TIME_TO_DIE];
	if (philo->info[NUM_OF_EAT] > 0)
		++(philo->cnt_eat);
}

void	action_sleep(t_philo *philo)
{
	printf("%llu %d is sleeping\n",
		   get_time() - philo->start_time, philo->idx_of_philo);
	philo_msleep(philo->info[TIME_TO_SLEEP], philo);
}
