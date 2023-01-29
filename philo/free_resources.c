#include "philosopher.h"

void    free_resources(t_philo_gen *philo_gen)
{
    int i;

    i = 0;
    while (i < philo_gen->num_of_philo)
    {
        pthread_mutex_destroy(&(philo_gen->forks[i]));
        i++;
    }
    free(philo_gen->forks);
    i = 0;
    while (i < philo_gen->num_of_philo)
    {
        pthread_detach(philo_gen->thread_id[i]);
        i++;
    }
    free(philo_gen->thread_id);
    free(philo_gen->philosophers);
}
