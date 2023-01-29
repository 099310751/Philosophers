#include "philosopher.h"

int init_forks(t_philo_gen *philo_gen)
{
    int i;

    i = 0;
    philo_gen->forks = malloc(sizeof(pthread_mutex_t) * philo_gen->num_of_philo);
    while (i < philo_gen->num_of_philo)
    {
        pthread_mutex_init(&philo_gen->forks[i], NULL);
        i++;
    }
    return (0);
}
