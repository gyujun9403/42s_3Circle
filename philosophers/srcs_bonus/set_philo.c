/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:26:27 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/25 15:56:16 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

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
	philo->anounce = ft_sem_open("anounce", 1);
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

void	post_sem(sem_t *sem, const int time)
{
	int	idx;

	idx = 0;
	while (idx++ < time)
		sem_post(sem);
}

void	free_philo(t_philo *philo)
{
	sem_unlink("forks");
	sem_close(philo->forks);
	sem_unlink("die");
	sem_close(philo->die);
	sem_unlink("die_check");
	sem_close(philo->die_check);
	post_sem(philo->full, philo->info[NUM_OF_PHILO]);
	sem_unlink("full");
	sem_close(philo->full);
	sem_unlink("anounce");
	sem_close(philo->anounce);
	free(philo->thread);
	free(philo->pids);
	free(philo);
}
