/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:47:47 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/21 16:47:53 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void action_eat(t_philo *philo)
{
	printf("%llu\t%d\tis eating\n", get_time(), philo->idx_of_philo);
	philo_msleep(philo->philo_info[TIME_TO_EAT], philo);
	philo->when_die = get_time() + philo->philo_info[TIME_TO_DIE];
	++philo->cnt_eat;
}

void action_sleep(t_philo *philo)
{
	printf("%llu\t%d\tis sleeping\n", get_time(), philo->idx_of_philo);
	philo_msleep(philo->philo_info[TIME_TO_SLEEP], philo);
}