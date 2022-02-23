/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philoopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:00:22 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/23 16:22:14 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef philoOPHERS_BONUS_H
# define philoOPHERS_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>

# define FALSE			0
# define TRUE			1
# define SUCCESS		0
# define FAILURE		1
# define ERR_NOT_NUM	-1
# define ERR_OUT_OF_INT	-2
# define INF			-10

# define NUM_OF_PHILO	0 
# define TIME_TO_DIE	1
# define TIME_TO_EAT	2
# define TIME_TO_SLEEP	3
# define NUM_OF_EAT		4
# define INT_MAX 2147483647

// t_philo는 배열 형태로 선언되므로, 시작주소만 안다면 mornitor에서 각 죽는 시간에 접근 가능.
typedef struct s_philo
{
	pid_t				*pids;
	int					idx_of_philo;
	int					*info;
	//pthread_mutex_t		forks[2];
	sem_t				*forks;
	sem_t				*full;
	sem_t				*die;
	sem_t				*die_check;
	pthread_t			*thread;
	//unsigned long long	start_time;
	unsigned long long	when_die;
	//int					*is_die;
	int					cnt_eat;
}	t_philo;

// actions
void				action_eat(t_philo *philo);
void				action_sleep(t_philo *philo);
//handler
int					hdl_not_legal_num(char *str);
int					hdl_out_of_int(char *str);
int					hdl_syscall(char *msg);
int					hdl_too_few_philo(void);

// parsing
int					parse_info(int parsed_input[5], char **av);

// mutexs
pthread_mutex_t		*init_mutexs(const int parsed_input[5]);
void				destroy_mutexs(t_philo *philo);

// pthreads
int					creat_pthreads(t_philo *philo);
void				join_pthreads(t_philo *philo);
int					routine(t_philo *philo);

// set_philo
t_philo	*			set_philo(const int parsed_input[5]);
void				free_philo(t_philo *philo);

// syscalls
void				*ft_malloc(size_t size);
sem_t				*ft_sem_open(const char *name, const unsigned int value);
void				*ft_calloc(size_t count, size_t size);

// utils
int					philo_atoi(char *str);
size_t				philo_strlen(const char *str);
void				philo_free_sstr(char **sstr, int size_str);

// time
void				philo_msleep(int msec);
unsigned long long	get_time(int start_time);
unsigned long long	get_elapsed_time(void);

#endif