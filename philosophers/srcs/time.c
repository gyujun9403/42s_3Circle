#include "../header/philosophers.h"

unsigned long long	get_time(void)
{
	struct timeval			tv;
	unsigned long long		result;

	gettimeofday(&tv, NULL);
	result = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (result);
}

void	philo_msleep(int msec, t_philo *philo)
{
	unsigned long long	time_end;
	unsigned long long	time_now;

	time_end = get_time() + msec;
	while (*philo->is_die == FALSE)
	{
		time_now = get_time();
		if  (time_now >= time_end)
			break;
		usleep(500);
	}
}