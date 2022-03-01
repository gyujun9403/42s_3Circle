/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyeon <gyeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 16:50:06 by gyeon             #+#    #+#             */
/*   Updated: 2022/02/28 00:18:22 by gyeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/philosopher_bonus.h"

int	philo_atoi(char *str)
{
	size_t			idx;
	unsigned int	result;

	idx = 0;
	result = 0;
	while (str[idx] != '\0')
	{
		if (str[idx] >= '0' && str[idx] <= '9')
		{
			result = result * 10 + str[idx] - '0';
			if (result > INT_MAX)
				return (ERR_OUT_OF_INT);
		}
		else
			return (ERR_NOT_NUM);
		++idx;
	}
	return (result);
}

size_t	philo_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}
