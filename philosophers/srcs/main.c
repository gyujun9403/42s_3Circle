/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/23 15:47:14 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	monitor(const t_philo *philo)
{
	int	idx;
	int	cnt_full;

	idx = 0;
	cnt_full = 0;
	while (*(philo->is_die) == FALSE)
	{
		if (philo[idx].when_die <= get_time())
		{
			*(philo->is_die) = TRUE;
			printf("%llu %d died\n",
				   get_time() - philo->start_time, philo[idx].idx_of_philo);
		}
		else if (philo->info[NUM_OF_EAT] != INF
			&& philo[idx].cnt_eat >= philo->info[NUM_OF_EAT])
			++cnt_full;
		if (++idx == philo->info[NUM_OF_PHILO])
		{
			if (cnt_full == idx)
				*(philo->is_die) = TRUE;
			cnt_full = 0;
			idx = 0;
		}
		sleep(500);
	}
}

int	main(int ac, char **av)
{
	unsigned long long	start_time;
	int					parsed_input[5];
	t_philo				*philos;

	start_time = get_time();
	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (parse_info(parsed_input, av) == FAILURE)
			return (FAILURE);
	philos = (t_philo *)malloc(sizeof(t_philo) * parsed_input[NUM_OF_PHILO]);
	if (philos == NULL)
		return (hdl_syscall("malloc"));
	philos->start_time = start_time;
	if (set_philos(philos, parsed_input) == FAILURE)
		return (FAILURE);
	creat_pthreads(philos);
	monitor(philos);
	join_pthreads(philos);
	destroy_mutexs(philos);
	free_philos(philos);
	return (SUCCESS);
}
