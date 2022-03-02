/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2022/03/01 15:57:55 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

void	*scheduler(void *in)
{
	t_philo	*philos;
	int		start;
	int		idx_at_once;
	int		num_at_once;

	start = 0;
	philos = (t_philo *)in;
	if (philos->info[NUM_OF_PHILO] % 2 == 0)
		num_at_once = philos->info[NUM_OF_PHILO] / 2;
	else
		num_at_once = (philos->info[NUM_OF_PHILO] - 1) / 2;
	while (1)
	{
		idx_at_once = 0;
		while (idx_at_once < num_at_once)
			pthread_mutex_unlock(philos[(start + idx_at_once++ *2)
				% philos->info[NUM_OF_PHILO]].restriction);
		idx_at_once = 0;
		while (idx_at_once < num_at_once)
			pthread_mutex_lock(philos[(start + idx_at_once++ *2)
				% philos->info[NUM_OF_PHILO]].eat);
		start = (start + 1) % philos->info[NUM_OF_PHILO];
		usleep(50);
	}
}

void	monitor(const t_philo *philo)
{
	int	idx;
	int	cnt_full;

	idx = 0;
	cnt_full = 0;
	while (*(philo->is_die) == FALSE)
	{
		if (philo[idx].when_die <= get_time(FALSE))
			mutex_prt_die(philo[idx].idx_of_philo,
				philo->anounce, philo->is_die, TRUE);
		else if (philo->info[NUM_OF_EAT] != INF
			&& philo[idx].cnt_eat >= philo->info[NUM_OF_EAT])
			++cnt_full;
		if (++idx == philo->info[NUM_OF_PHILO])
		{
			if (cnt_full == idx)
				mutex_prt_die(philo[idx].idx_of_philo,
					philo->anounce, philo->is_die, FALSE);
			cnt_full = 0;
			idx = 0;
		}
	}
}

int	main(int ac, char **av)
{
	int					parsed_input[5];
	t_philo				*philos;
	pthread_t			p_scheduler;

	get_time(TRUE);
	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (parse_info(parsed_input, av) == FAILURE)
			return (FAILURE);
	philos = set_philos(parsed_input);
	if (philos == NULL)
		return (FAILURE);
	pthread_create(&p_scheduler, NULL, scheduler, (void *)philos);
	creat_pthreads(philos);
	monitor(philos);
	pthread_detach(p_scheduler);
	detach_pthreads(philos);
	destroy_mutexs(philos);
	free_philos(philos);
	return (SUCCESS);
}
