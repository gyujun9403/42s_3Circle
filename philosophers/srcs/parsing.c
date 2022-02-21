#include "../header/philosophers.h"

int	check_info(const int parsed_input[5], char **av)
{
	size_t	idx;
	int		result_flag;

	result_flag = SUCCESS;
	if (parsed_input[0] == 1 || parsed_input[0] == 0)
		result_flag = hdl_too_few_philo();
	else
	{
		idx = 0;
		while (idx < 5)
		{
			if (parsed_input[idx] == ERR_NOT_NUM)
				result_flag = hdl_not_legal_num(av[idx + 1]);
			else if (parsed_input[idx] == ERR_OUT_OF_INT)
				result_flag = hdl_out_of_int(av[idx + 1]);
			++idx;
		}
	}
	return (result_flag);
}

/*
** info[0] : number_of_philosophers
** info[1] : time_to_die
** info[2] : time_to_eat
** info[3] : time_to_sleep
** info[4] : number_of_times_each_philosopher_must_eat
*/
int	parse_info(int parsed_input[5], char **av)
{
	size_t	idx;

	idx = 0;
	while (idx < 4)
	{
		parsed_input[idx] = philo_atoi(av[idx + 1]);
		++idx;
	}
	if (av[5] != NULL)
		parsed_input[4] = philo_atoi(av[5]);
	else
		parsed_input[4] = INF;
	return (check_info(parsed_input, av));
}