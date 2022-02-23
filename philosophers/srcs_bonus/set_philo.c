/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:26:27 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/23 17:55:59 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

/*
**					   left / right
** thread[0]	: mutex[0]	/ mutex[1]
** thread[1]	: mutex[1]	/ mutex[2]
** thread[2]	: mutex[2]	/ mutex[3]
** thread[n-1]	: mutex[n-1] / mutex[0]
*/
// void	init_philo(t_philo *philo, pthread_t *threads,
// 	 pthread_mutex_t *mutexs, const int *parsed_input)
// {
// 	int		idx;

// 	idx = 0;
// 	*(philo->is_die) = FALSE;
// 	while (idx < parsed_input[NUM_OF_PHILO])
// 	{
// 		philo[idx].idx_of_philo = idx;
// 		philo[idx].forks[0] = mutexs[idx];
// 		if (idx + 1 == parsed_input[NUM_OF_PHILO])
// 			philo[idx].forks[1] = mutexs[0];
// 		else
// 			philo[idx].forks[1] = mutexs[idx + 1];
// 		philo[idx].info = (int *)parsed_input;
// 		philo[idx].thread = threads[idx];
// 		philo[idx].is_die = philo->is_die;
// 		philo[idx].cnt_eat = 0;
// 		philo[idx].start_time = philo->start_time;
// 		++idx;
// 	}
// }

/*
typedef struct s_philo
{
	int					idx_of_philo;
	int					*info;
	sem_t				*forks;
	sem_t				*full;
	sem_t				*die;
	sem_t				*die_check;
	pthread_t			thread;
	unsigned long long	start_time;
	unsigned long long	when_die;
	int					*is_die;
	int					cnt_eat;
}	t_philo;
*/

/* 
일단...idx of philo는 fork후 탈출한 idx. 가장 큰 값은 최상위 부모.
forks, full, die, sem_open(철학자 수) / die_check는 하나.
thread는 각각 하나씩인데, 최상위 부모는 fullcheck / 자식들은 die_check용도.
	최상위 부모에서 메인 thread는 die_check, 다른 thread는 조건에 따라 full_check
	자식들은 메인 thread는 일상, 다른 thread는 die_check돈다. 이때 usleep(500)정도 간격으로 

fork 전에 full과 die의 모든 세마포어를 점유 시켜놓고 시작. 이후 full되거나 die될때마다 하나씩 post
[부모 프로세스]
	메인 : sem_wait(die). 하나라도 되면 바로 kill(pids)
	서브 : sem_wait(full). 철학자 개수만큼 full 되면 kill(pids)
[자식프로세스]
	메인 : 루틴 실행. 밥 다먹고 획수 다 채웠으면 full post정도만 **주의! 단 1회만 하게.**
	서브 : sem_wait(die_check)를 usleep(500)간격으로?. 바쁜대기를 시키지 않고 세마포어를 통해 자동으로 큐대기로순차적 실행하게 한다.
		만약 죽었으면(현재시간 > 죽은시간)이면 죽음 출력 및 die를 post한다.
*/

int	occupy_sem(sem_t *sem, const int time)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
	{
		if (sem_wait(sem) != 0)
			return (FAILURE);
	}
	return (SUCCESS);
}


t_philo	*set_philo(const int parsed_input[5])
{
	t_philo	*philo;
	
	philo = (t_philo *)ft_malloc(sizeof(t_philo));
	philo->thread = (pthread_t *)ft_malloc(sizeof(pthread_t));
	philo->pids = (int *)ft_calloc(sizeof(int), parsed_input[NUM_OF_PHILO]);
	philo->full = ft_sem_open("full", parsed_input[NUM_OF_PHILO]);
	philo->forks = ft_sem_open("forks", parsed_input[NUM_OF_PHILO]);
	philo->die = ft_sem_open("die", parsed_input[NUM_OF_PHILO]);
	philo->die_check = ft_sem_open("die_check", 1);
	if (occupy_sem(philo->full, parsed_input[NUM_OF_PHILO]) == FAILURE
		|| occupy_sem(philo->die, parsed_input[NUM_OF_PHILO]) == FAILURE)
	{
		free_philo(philo);
		return (NULL);
	}
	philo->cnt_eat = 0;
	philo->info = (int *)parsed_input;
	return (philo);
}

void	free_philo(t_philo *philo)
{
	sem_unlink("full");
	sem_close(philo->full);
	sem_unlink("forks");
	sem_close(philo->forks);
	sem_unlink("die");
	sem_close(philo->die);
	sem_unlink("die_check");
	sem_close(philo->die_check);
	free(philo->thread);
	free(philo);
}
