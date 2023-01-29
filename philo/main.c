#include "philosopher.h"

int main(int argc, char **argv)
{
    t_philo_gen    *philo_gen;

    if (argc < 5)
    {
        printf("Not enough arguments\n");
        return (1);
    }
    if (!(philo_gen = (t_philo_gen *)malloc(sizeof(t_philo_gen))))
        return (1);
    philo_gen->num_of_philo = ft_atoi(argv[1]);
    philo_gen->time_to_die = ft_atoi(argv[2]);
    philo_gen->time_to_eat = ft_atoi(argv[3]);
    philo_gen->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        philo_gen->num_of_must_eat = ft_atoi(argv[5]);
    else
        philo_gen->num_of_must_eat = -1;
    t_philo *philo  =malloc(sizeof(t_philo) * philo_gen->num_of_philo);
    philo_gen->forks = malloc(sizeof(pthread_mutex_t) * philo_gen->num_of_philo);
    philo_gen->philosophers = philo;
    if (init_philosophers(philo_gen))
        return (1);
    do_work(philo_gen);
   /* if (init_forks(philo_gen))
        return (1);
    if (create_philo(philo_gen))
        return (1);
    if (join_philo(philo_gen))
        return (1);
    free_resources(philo_gen);
    return (0);*/
    return (0);
}
