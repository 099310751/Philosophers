#include "philosopher.h"

void    check_die(t_philo_gen *philo_gen, t_philo *philosophers)
{
    int i;

    i = 0;
    while (i < philo_gen->num_of_philo)
    {
        if (philosophers[i].is_dead == 1)
        {
            printf("Philosopher %d died\n", i + 1);
            exit(0);
        }
        i++;
    }
}
