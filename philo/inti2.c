#include "philosopher.h"

int	is_death(t_philo_gen	**head)
{
	if (gettime_milisec() - (*head)->philosophers[(*head)->i].last_eat_time \
		>= (*head)->time_to_die \
		&& (*head)->philosophers[(*head)->i].finished_flag == 0)
	{
		printf("%llu %u is died\n", \
				gettime_milisec(), \
				(*head)->philo_x[(*head)->i].id);
		return (-1);
	}
	return (0);
}

int	simulation_loop(t_main **head)
{
	(*head)->count_finished_philos = 0;
	while (1)
	{
		(*head)->i = 0;
		while ((*head)->i < (*head)->number_of_philo)
		{
			if ((*head)->count_finished_philos == (*head)->number_of_philo)
				return (1);
			if (is_death(&(*head)) == -1)
				return (-1);
			if ((*head)->philo_x[(*head)->i].finished_flag == 1)
			{
				(*head)->philo_x[(*head)->i].finished_flag++;
				(*head)->count_finished_philos++;
			}
			(*head)->i++;
		}
	}
	return (0);
}

int	algo_loop(t_philo **head)
{
	t_philo	*data;

	data = *head;
	while (1)
	{
		eating_loop(&data);
		data->contenue_time = gettime_milisec();
		data->count_eating_time++;
		if (data->count_eating_time == data->count_time_to_eat)
		{
			printf("%llu %u philo has finished simulation\n", \
			data->contenue_time, data->id);
			data->finished_flag++;
			return (0);
		}
		printf("%llu %u fall a sleep\n", data->contenue_time, data->id);
		ft_msleep(data->time_to_sleep);
		data->contenue_time = gettime_milisec();
		printf("%llu %u is thinking\n", data->contenue_time, data->id);
	}
	return (0);
}

void	eating_loop(t_philo **head)
{
	t_philo	*data;

	data = *head;
	pthread_mutex_lock(data->left);
	printf("%llu %u has taken a left fork\n", \
	data->contenue_time, data->id);
	pthread_mutex_lock(data->right);
	printf("%llu %u has taken a right fork\n", \
	data->contenue_time, data->id);
	data->last_eat_time = gettime_milisec();
	printf("%llu %u is eating\n", data->contenue_time, data->id);
	ft_msleep(data->time_to_eat);
	pthread_mutex_unlock(data->left);
	pthread_mutex_unlock(data->right);
}