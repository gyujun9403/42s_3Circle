/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:00:22 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/21 19:01:32 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdio.h>

#define FALSE			0
#define TRUE			1
#define	SUCCESS			0
#define	FAILURE			1
#define ERR_NOT_NUM		-1
#define ERR_OUT_OF_INT	-2
#define INF				-10

#define NUM_OF_PHILO	0
#define TIME_TO_DIE		1
#define TIME_TO_EAT		2
#define TIME_TO_SLEEP	3
#define NUM_OF_EAT		4
#define INT_MAX 2147483647

typedef struct s_setting
{
	int				philo_info[5];
		pthread_mutex_t	*mutexs;
		pthread_t 		*thread;
} t_setting;

typedef struct s_philo
{
	int				idx_of_philo;
	int				*philo_info;
	pthread_mutex_t	forks[2];
	pthread_t 		thread;
	// t_philo는 배열 형태로 선언되므로, 시작주소만 안다면 mornitor에서 각 죽는 시간에 접근 가능.
	unsigned long long	when_die;
	int 			*is_die;
	int 			cnt_eat;
} t_philo;
// actions
void action_eat(t_philo *philo);
void action_sleep(t_philo *philo);
//handler
int	hdl_not_legal_num(char *str);
int	hdl_out_of_int(char *str);
int	hdl_syscall(char *msg);
int	hdl_too_few_philo(void);

//utils
int philo_atoi(char *str);
size_t philo_strlen(const char *str);
void philo_free_sstr(char **sstr, int size_str);

// time
void	philo_msleep(int msec, t_philo *philo);
unsigned long long	get_time(void);

#endif