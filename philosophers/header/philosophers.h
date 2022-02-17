/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 18:00:22 by gyeon             #+#    #+#             */
/*   Updated: 2021/11/29 11:22:11 by gyeon            ###   ########.fr       */
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
#define INT_MAX 2147483647

typedef struct s_philos
{
	int				philo_info[5];
	pthread_mutex_t	*mutexs;
	pthread_t 		*thread;
} t_philos;


//handler
int	hdl_not_legal_num(char *str);
int	hdl_out_of_int(char *str);
int	hdl_syscall(char *msg);

//utils
int philo_atoi(char *str);
size_t philo_strlen(const char *str);
void philo_free_sstr(char **sstr, int size_str);

#endif