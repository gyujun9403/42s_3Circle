//
// Created by 연규준 on 2022/02/17.
//

#include "../header/philosophers.h"

int philo_atoi(char *str)
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

size_t philo_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	return (i);
}

void philo_free_sstr(char **sstr, int size_str)
{
	int idx;

	idx = 0;
	while (idx < size_str)
		free(sstr[idx++]);
	free(sstr);
}