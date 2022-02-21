/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:21:51 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/21 19:03:29 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosophers.h"

int	check_philo_info(int parsed_input[5], char **av)
{
	size_t	idx;
	int result_flag;

	result_flag = SUCCESS;
	if (parsed_input[0] == 1 || parsed_input[0] == 0)
		result_flag = hdl_too_few_philo();
	else
	{
		idx = 0;
		while (idx < 5)
		{
			if (parsed_input[idx] == ERR_NOT_NUM)
				result_flag = hdl_not_legal_num(av[idx + 1]);
			else if (parsed_input[idx] == ERR_OUT_OF_INT)
				result_flag = hdl_out_of_int(av[idx + 1]);
			++idx;
		}
	}
	return (result_flag);
}

int	parse_philo_info(int parsed_input[5], char **av)
{
	size_t idx;

	idx = 0;
	while (idx < 4)
	{
		parsed_input[idx] = philo_atoi(av[idx + 1]);
		++idx;
	}
	if (av[5] != NULL)
		parsed_input[4] = philo_atoi(av[5]);
	else
		parsed_input[4] = INF;
	return (check_philo_info(parsed_input, av));
}

pthread_mutex_t *init_mutexs(int parsed_input[5])
{
	int				idx;
	pthread_mutex_t	*result;

	idx = 0;
	result = (pthread_mutex_t *)malloc
			(sizeof(pthread_mutex_t) * parsed_input[NUM_OF_PHILO]);
	if (result == NULL)
	{
		hdl_syscall("malloc");
		return (NULL);
	}
	while (idx < parsed_input[NUM_OF_PHILO])
	{
		if (pthread_mutex_init(&result[idx], NULL) != SUCCESS) {
			hdl_syscall("pthread_mutex_init");
			while (idx > 0)
				pthread_mutex_destroy(&result[--idx]);
			free(result);
			return (NULL);
		}
		++idx;
	}
	return (result);
}

void destroy_mutexs(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->philo_info[NUM_OF_PHILO])
		pthread_mutex_destroy(&philos[idx++].forks[0]);
}

/*
**				  left/right
** thread[0]	: mutex[0] / mutex[1]
** thread[1]	: mutex[1] / mutex[2]
** thread[2]	: mutex[2] / mutex[3]
** thread[n-1]	: mutex[n-1] / mutex[0]
 * 해당 함수가 특정 스레드로 돌아가고 있는지 어떻게 알지??
 * -> 매개변수도 다 넘길게 아니라, 사용할 스레드/뮤텍스만 담을 구조체ㅐ를 만들어서 보내기.
*/
void *routine(void *philo)
{
	t_philo *casted_philo;

	casted_philo = (t_philo *)philo;
	// 죽는시간 체크하고
	casted_philo->when_die = get_time() + casted_philo->philo_info[TIME_TO_DIE];
	// 죽거나, 밥을 다 먹을때까지 무한루프
	while (*(casted_philo->is_die) == FALSE)
	{
		printf("%llu\t%d\tis thinking\n", get_time(), casted_philo->idx_of_philo);
		pthread_mutex_lock(&casted_philo->forks[0]);
		printf("%llu\t%d\tis has taken a fork\n", get_time(), casted_philo->idx_of_philo);
		pthread_mutex_lock(&casted_philo->forks[1]);
		printf("%llu\t%d\tis has taken a fork\n", get_time(), casted_philo->idx_of_philo);
		action_eat(philo);
		pthread_mutex_unlock(&casted_philo->forks[1]);
		pthread_mutex_unlock(&casted_philo->forks[0]);
		action_sleep(philo);
	}
	return (NULL);
}

void	monitor(t_philo *philo)
{
	int idx;

	idx = 0;
	while (1)
	{
		if (philo[idx].when_die <= get_time())
		{
			*philo[idx].is_die = TRUE;
			printf("%llu\t%d\tdied\n", get_time(), philo[idx].idx_of_philo);
			break;
		}
		if (++idx == philo->philo_info[NUM_OF_PHILO])
			idx = 0;
	}
}

int creat_pthreads(t_philo *philos)
{
	int			idx;

	idx = 0;
	while(idx < philos->philo_info[NUM_OF_PHILO])
	{
		pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]);
		++idx;
	}
	return (SUCCESS);
}

void join_pthreads(t_philo *philos)
{
	int idx;

	idx = 0;
	while(idx < philos->philo_info[NUM_OF_PHILO])
		pthread_join(philos[idx++].thread, NULL);
}

void	init_philos(t_philo *philos, pthread_t *threads, pthread_mutex_t *mutexs, int parsed_input[5])
{
	int		idx;
	int		*is_die;
	
	idx = 0;
	is_die = philos->is_die;
	is_die = FALSE;
	while(idx < parsed_input[NUM_OF_PHILO])
	{
		philos[idx].idx_of_philo = idx;
		philos[idx].forks[0] = mutexs[idx];
		if (idx + 1 == parsed_input[NUM_OF_PHILO])
			philos[idx].forks[1] = mutexs[0];
		else
			philos[idx].forks[1] = mutexs[idx + 1];
		philos[idx].philo_info = parsed_input;
		philos[idx].thread = threads[idx];
		philos[idx].is_die = is_die;
		philos[idx].cnt_eat = 0;
		++idx;
	}
}

int	make_philos(t_philo **philos, int parsed_input[5])
{
	pthread_t		*threads;
	pthread_mutex_t	*mutexs;

	mutexs = init_mutexs(parsed_input);
	if (mutexs == NULL)
		return (FALSE);
	*philos = (t_philo *)malloc(sizeof(t_philo) * parsed_input[NUM_OF_PHILO]);
	if (philos == NULL)
		return (hdl_syscall("malloc"));
	else
	{
		(*philos)->is_die = (int *)malloc(sizeof(int) * 1);
		if ((*philos)->is_die == NULL)
			return (hdl_syscall("malloc"));
		else
		{
			threads = (pthread_t *)malloc(sizeof(pthread_t) * parsed_input[NUM_OF_PHILO]);
			if (threads == NULL)
				return (hdl_syscall("pthread"));
		}
	}
	init_philos(*philos, threads, mutexs, parsed_input);
	free(mutexs);
	free(threads);
	return (SUCCESS);
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
	int		parsed_input[5];
	t_philo	*philos;

	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (parse_philo_info(parsed_input, av) == FAILURE)
			return (FAILURE);
	if (make_philos(&philos, parsed_input) == FAILURE)
		return (FAILURE);
	creat_pthreads(philos);
	monitor(philos);
	join_pthreads(philos);
	destroy_mutexs(philos);
	return (SUCCESS);
}