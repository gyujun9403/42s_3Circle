/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 17:43:01 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/24 20:39:48 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	mutex_prt_eat(const int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%llu %d is eating\n", get_elapsed_time(), num);
	pthread_mutex_unlock(mutex);
}

void	mutex_prt_fork(const int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%llu %d has taken a fork\n", get_elapsed_time(), num);
	pthread_mutex_unlock(mutex);
}

void	mutex_prt_sleep(const int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%llu %d is sleeping\n", get_elapsed_time(), num);
	pthread_mutex_unlock(mutex);
}

void	mutex_prt_think(const int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%llu %d is thinking\n", get_elapsed_time(), num);
	pthread_mutex_unlock(mutex);
}

void	mutex_prt_die(const int num, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%llu %d die\n", get_elapsed_time(), num);
}
