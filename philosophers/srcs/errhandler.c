//
// Created by 연규준 on 2022/02/17.
//

#include "../header/philosophers.h"

int	hdl_syscall(char *msg)
{
	write(2, msg, philo_strlen(msg));
	write(2, " system call false!\n", 20);
	return (FAILURE);
}

int	hdl_not_legal_num(char *str)
{
	write(2, str, philo_strlen(str));
	write(2, " is illegal input\nUse positive integer numbers.\n", 48);
	return (FAILURE);
}

int	hdl_out_of_int(char *str)
{
	write(2, str, philo_strlen(str));
	write(2, " is out of INT area\nUse positive integer numbers.\n", 50);
	return (FAILURE);
}