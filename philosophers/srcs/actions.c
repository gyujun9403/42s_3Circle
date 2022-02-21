//
// Created by 연규준 on 2022/02/19.
//

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