/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:00 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/24 20:40:50 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

unsigned long long	get_time(int get_start_time)
{
	static unsigned long long	start_time = 0ull;
	struct timeval				tv;
	unsigned long long			result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	if (get_start_time == TRUE)
	{
		if (start_time == 0)
			start_time = result;
		return (start_time);
	}
	return (result);
}

void	philo_msleep(int msec, t_philo *philo)
{
	unsigned long long	time_end;

	time_end = get_time(FALSE) + msec;
	while (*(philo->is_die) == FALSE)
	{
		if (get_time(FALSE) >= time_end)
			break ;
		usleep(700);
	}
}

unsigned long long	get_elapsed_time(void)
{
	return (get_time(FALSE) - get_time(TRUE));
}
