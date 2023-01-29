/*#include "philosopher.h"

int join_philo(t_philo_gen *philo_gen)
{
    int i;
    for (i = 0; i < philo_gen->num_of_philo; i++)
    {
        pthread_join(philo_gen->philosophers[i].thread, NULL);
    }
    return (0);
}
