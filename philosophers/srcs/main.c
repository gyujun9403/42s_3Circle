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

int	check_philo_info(t_setting *setting, char **av)
{
	size_t	idx;
	int result_flag;

	idx = 0;
	result_flag = SUCCESS;
	while (idx < 5)
	{
		if (setting->philo_info[idx] == ERR_NOT_NUM)
			result_flag = hdl_not_legal_num(av[idx + 1]);
		else if (setting->philo_info[idx] == ERR_OUT_OF_INT)
			result_flag = hdl_out_of_int(av[idx + 1]);
		++idx;
	}
	return (result_flag);
}

int	set_philo_info(t_setting *setting, char **av)
{
	size_t idx;

	idx = 0;
	while (idx < 4)
	{
		setting->philo_info[idx] = philo_atoi(av[idx + 1]);
		++idx;
	}
	if (av[5] != NULL)
		setting->philo_info[4] = philo_atoi(av[5]);
	else
		setting->philo_info[4] = INF;
	return (check_philo_info(setting, av));
}

int init_mutexs(t_setting *setting)
{
	int idx;

	idx = 0;
	setting->mutexs = (pthread_mutex_t *)malloc
			(sizeof(pthread_mutex_t) * setting->philo_info[0]);
	if (setting->mutexs == NULL)
	{
		hdl_syscall("malloc");
		return (FAILURE);
	}
	while (idx < setting->philo_info[0])
	{
		if (pthread_mutex_init(&setting->mutexs[idx], NULL) != SUCCESS) {
			hdl_syscall("mutex_init");
			while (idx > 0)
				pthread_mutex_destroy(&setting->mutexs[--idx]);
			free(setting->mutexs);
			return (FAILURE);
		}
		++idx;
	}
	return (SUCCESS);
}

void destroy_mutexs(t_setting *setting)
{
	int	idx;

	idx = 0;
	while (idx < setting->philo_info[0])
		pthread_mutex_destroy(&setting->mutexs[idx++]);
	free(setting->mutexs);
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
	}
	printf("%llu\t%d\tis END\n", get_time(), casted_philo->idx_of_philo);
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

int creat_pthreads(t_setting *setting)
{
	int			idx;
	pthread_t	*threads;
	t_philo 	*philo;
	int 		*is_die;

	threads = (pthread_t *)malloc(sizeof(pthread_t) * setting->philo_info[0]);
	if (threads == NULL)
		return (hdl_syscall("pthread"));

	philo = (t_philo *)malloc(sizeof(t_philo) * setting->philo_info[0]);
	if (philo == NULL)
		return (hdl_syscall("malloc"));
	is_die = (int *)malloc(sizeof(int) * 1);
	if (is_die == NULL)
		return (hdl_syscall("malloc"));
	*is_die = FALSE;
	idx = 0;
	while(idx < setting->philo_info[0])
	{
		philo[idx].idx_of_philo = idx;
		philo[idx].forks[0] = setting->mutexs[idx];
		if (idx + 1 == setting->philo_info[0])
			philo[idx].forks[1] = setting->mutexs[0];
		else
			philo[idx].forks[1] = setting->mutexs[idx + 1];
		philo[idx].philo_info = setting->philo_info;
		philo[idx].thread = setting->thread[idx];
		philo[idx].is_die = is_die;
		philo[idx].cnt_eat = 0;
		++idx;
	}
	idx = 0;
	while(idx < setting->philo_info[0])
	{
		pthread_create(&threads[idx], NULL, routine, &philo[idx]);
		++idx;
	}
	monitor(philo);
	return (SUCCESS);
}

void join_pthreads(t_setting *setting)
{
	int idx;

	idx = 0;
	while(idx < setting->philo_info[0])
		pthread_join(setting->thread[idx++], NULL);
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
	t_setting	setting;

	if (ac != 5 && ac != 6)
		return (FAILURE);
	else
		if (set_philo_info(&setting, av) == FAILURE)
			return (FAILURE);
	if (init_mutexs(&setting) == FAILURE)
		return (FAILURE);
	creat_pthreads(&setting);
	join_pthreads(&setting);
	destroy_mutexs(&setting);

	return (SUCCESS);
}