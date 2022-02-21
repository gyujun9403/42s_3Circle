#include "../header/philosophers.h"

void	*routine(void *philo)
{
	t_philo	*cast_philo;

	cast_philo = (t_philo *)philo;
	cast_philo->when_die
		= cast_philo->start_time + cast_philo->info[TIME_TO_DIE];
	while (*(cast_philo->is_die) == FALSE)
	{
		printf("%llu %d is thinking\n", get_time() - cast_philo->start_time,
			   cast_philo->idx_of_philo);
		pthread_mutex_lock(&(cast_philo->forks[0]));
		printf("%llu %d is has taken a fork\n",
			   get_time() - cast_philo->start_time,
			   cast_philo->idx_of_philo);
		pthread_mutex_lock(&(cast_philo->forks[1]));
		printf("%llu %d is has taken a fork\n",
			   get_time() - cast_philo->start_time,
			   cast_philo->idx_of_philo);
		action_eat(philo);
		pthread_mutex_unlock(&(cast_philo->forks[1]));
		pthread_mutex_unlock(&(cast_philo->forks[0]));
		action_sleep(philo);
	}
	return (NULL);
}

int	creat_pthreads(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->info[NUM_OF_PHILO])
	{
		pthread_create(&philos[idx].thread, NULL, routine, &philos[idx]);
		++idx;
	}
	return (SUCCESS);
}

void	join_pthreads(t_philo *philos)
{
	int	idx;

	idx = 0;
	while (idx < philos->info[NUM_OF_PHILO])
		pthread_join(philos[idx++].thread, NULL);
}