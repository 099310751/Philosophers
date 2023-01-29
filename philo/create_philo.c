#include "philosopher.h"

int create_philo(t_philo_gen *philo_gen)
{
    int i;

    i = 0;
    while (i < philo_gen->num_of_philo)
    {
        if ((pthread_create(&(philo_gen->thread_id[i]), NULL, ft_thread_handler, ((void *)&(philo_gen->philo[i])))) != 0)
            return (1);
        i++;
    }
    check_die(philo_gen, philo_gen->philo);
    return (0);
}