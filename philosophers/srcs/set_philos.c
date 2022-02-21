#include "../header/philosophers.h"

/*
**				  left/right
** thread[0]	: mutex[0] / mutex[1]
** thread[1]	: mutex[1] / mutex[2]
** thread[2]	: mutex[2] / mutex[3]
** thread[n-1]	: mutex[n-1] / mutex[0]
 * 해당 함수가 특정 스레드로 돌아가고 있는지 어떻게 알지??
 * -> 매개변수도 다 넘길게 아니라, 사용할 스레드/뮤텍스만 담을 구조체ㅐ를 만들어서 보내기.
*/
void	init_philos(t_philo *philos, pthread_t *threads,
	 pthread_mutex_t *mutexs, const int *parsed_input)
{
	int		idx;

	idx = 0;
	*(philos->is_die) = FALSE;
	while (idx < parsed_input[NUM_OF_PHILO])
	{
		philos[idx].idx_of_philo = idx;
		philos[idx].forks[0] = mutexs[idx];
		if (idx + 1 == parsed_input[NUM_OF_PHILO])
			philos[idx].forks[1] = mutexs[0];
		else
			philos[idx].forks[1] = mutexs[idx + 1];
		philos[idx].info = (int *)parsed_input;
		philos[idx].thread = threads[idx];
		philos[idx].is_die = philos->is_die;
		philos[idx].cnt_eat = 0;
		philos[idx].start_time = philos->start_time;
		++idx;
	}
}

int	set_philos(t_philo *philos, const int parsed_input[5])
{
	pthread_t		*threads;
	pthread_mutex_t	*mutexs;

	mutexs = init_mutexs(parsed_input);
	if (mutexs == NULL)
		return (FALSE);
	else
	{
		philos->is_die = (int *)malloc(sizeof(int) * 1);
		if (philos->is_die == NULL)
			return (hdl_syscall("malloc"));
		else
		{
			threads = (pthread_t *)
				malloc(sizeof(pthread_t) * parsed_input[NUM_OF_PHILO]);
			if (threads == NULL)
				return (hdl_syscall("pthread"));
		}
	}
	init_philos(philos, threads, mutexs, parsed_input);
	free(mutexs);
	free(threads);
	return (SUCCESS);
}
