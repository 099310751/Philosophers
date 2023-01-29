#include "philosopher.h"

void	*routine(void *head)
{
	t_philo *data;

	data = head;
	data->count_eating_time = 0;
	data->contenue_time = gettime_milisec();
	data->last_eat_time = gettime_milisec();
	data->finished_flag = 0;
	if (data->id % 2 == 0)
		usleep(50);
	algo_loop(&data);
	return (0);
}

int	do_work(t_philo_gen *arg)
{
	unsigned int	i;

	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_mutex_init(&arg->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_create(&(arg->philosophers[i].philo), \
				NULL, &routine, &(arg->philosophers[i]));
		pthread_detach(arg->philo_x[i].philosophers);
		i++;
	}
	usleep(100);
	simulation_loop(&arg);
	i = 0;
	while (i < arg->num_of_philo)
	{
		pthread_mutex_destroy(&arg->forks[i]);
		i++;
	}
	return (0);
}