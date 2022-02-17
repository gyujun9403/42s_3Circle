/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2021/11/29 11:22:07 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	check_philo_info(t_philos *philos, char **av)
{
	size_t	idx;
	int result_flag;

	idx = 0;
	result_flag = SUCCESS;
	while (idx < 5)
	{
		if (philos->philo_info[idx] == ERR_NOT_NUM)
			result_flag = hdl_not_legal_num(av[idx + 1]);
		else if (philos->philo_info[idx] == ERR_OUT_OF_INT)
			result_flag = hdl_out_of_int(av[idx + 1]);
		++idx;
	}
	return (result_flag);
}

int	set_philo_info(t_philos *philos, char **av)
{
	size_t idx;

	idx = 0;
	while (idx < 4)
	{
		philos->philo_info[idx] = philo_atoi(av[idx + 1]);
		++idx;
	}
	if (av[5] != NULL)
		philos->philo_info[4] = philo_atoi(av[5]);
	else
		philos->philo_info[4] = INF;
	return (check_philo_info(philos, av));
}

int init_mutexs(t_philos *philos)
{
	int idx;

	idx = 0;
	philos->mutexs = (pthread_mutex_t *)malloc
			(sizeof(pthread_mutex_t) * philos->philo_info[0]);
	if (philos->mutexs == NULL)
	{
		hdl_syscall("malloc");
		return (FAILURE);
	}
	while (idx < philos->philo_info[0])
	{
		if (pthread_mutex_init(&philos->mutexs[idx], NULL) != SUCCESS) {
			hdl_syscall("mutex_init");
			while (idx > 0)
				pthread_mutex_destroy(&philos->mutexs[--idx]);
			free(philos->mutexs);
			return (FAILURE);
		}
		++idx;
	}
	return (SUCCESS);
}

void destroy_mutexs(t_philos *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->philo_info[0])
		pthread_mutex_destroy(&philos->mutexs[idx++]);
	free(philos->mutexs);
}

void *routine(void *philos)
{
	philos = (t_philos *)philos;

}

int creat_pthreads(t_philos *philos)
{
	int			idx;
	pthread_t	*threads;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * philos->philo_info[0]);
	if (threads == NULL)
		return (hdl_syscall("pthread"));
	idx = 0;
	while(idx < philos->philo_info[0])
		pthread_create(&threads[idx], NULL, routine, philos);
}

void join_pthreads(t_philos *philos)
{
	int idx;

	idx = 0;
	while(idx < philos->philo_info[0])
		pthread_join(philos->thread[idx++], NULL);
}

/*
** philo_info[0] : number_of_philosophers
** philo_info[1] : time_to_die
** philo_info[2] : time_to_eat
** philo_info[3] : time_to_sleep
** philo_info[4] : number_of_times_each_philosopher_must_eat
*/
int main(int ac, char **av)
{
	t_philos	philos;

	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (set_philo_info(philos.philo_info, av) == FAILURE)
			return (FAILURE);
	if (init_mutexs(&philos) == FAILURE)
		return (FAILURE);
	routine((void *)&philos);
	join_pthreads(&philos);
	destroy_mutexs(&philos);
	return (SUCCESS);
}