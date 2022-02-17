/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:10:25 by gyeon             #+#    #+#             */
/*   Updated: 2021/11/22 18:27:36 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void prt_help() {
	printf("philo: illegal options.\nuseage: \
	./philo number_of_philosophers \
	time_to_die time_to_eat \
	time_to_sleep \
	[number_of_times_each_philosopher_must_eat]");
}