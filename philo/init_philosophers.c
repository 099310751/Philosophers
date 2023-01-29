#include "philosopher.h"
#include "utility.h"

int init_philosophers(t_philo_gen *philo_gen)
{
    int i;

    i = 0;
    
    while (i + 1< philo_gen->num_of_philo)
    {
        philo_gen->philosophers[i].id = i + 1;
        philo_gen->philosophers[i].time_of_start = gettime_milisec();
        philo_gen->philosophers[i].left = philo_gen->forks[i];
        philo_gen->philosophers[i].right = philo_gen->forks[i + 1];
        philo_gen->philosophers[i].num_of_must_eat = philo_gen->num_of_must_eat;
        philo_gen->philosophers[i].time_to_sleep = philo_gen->time_to_sleep;
        philo_gen->philosophers[i].time_to_eat = philo_gen->time_to_eat;
        i++;
    }
    philo_gen->philosophers[i].id = i + 1;
    philo_gen->philosophers[i].time_of_start = gettime_milisec();
    philo_gen->philosophers[i].left = philo_gen->forks[i];
    philo_gen->philosophers[i].right = philo_gen->forks[0];
    philo_gen->philosophers[i].num_of_must_eat = philo_gen->num_of_must_eat;
    philo_gen->philosophers[i].time_to_sleep = philo_gen->time_to_sleep;
    philo_gen->philosophers[i].time_to_eat = philo_gen->time_to_eat;
    return (0);
}
