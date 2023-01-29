#ifndef PHILOSOPHER_H
#define PHILOSOPHER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct  s_philo
{
    int         finished_flag;
    int         id;
    int         num_of_eat;
    int         num_of_must_eat;
    int         eat_count;
    int         state;
    long long   time_of_start;
    pthread_t   thread;
    pthread_mutex_t rigth;
    pthread_mutex_t left;
    int         time_to_sleep;
    int         time_to_eat;
    unsigned long long contenue_time;
    unsigned long long last_eat_timme;
    unsigned long long count_eating time;
}               t_philo;

typedef struct  s_philo_gen
{
    int         num_of_philo;
    int         time_to_die;
    int         time_to_eat;
    int         time_to_sleep;
    t_philo         *philosophers;
    int         num_of_must_eat;
    t_philo     *philo;
    pthread_t   *thread_id;
    pthread_mutex_t *forks;
    unsigned int    count_finished_philos;
}               t_philo_gen;

void         *ft_thread_handler(void *philo);
int         init_philosophers(t_philo_gen *philo_gen);
int          init_forks(t_philo_gen *philo_gen);
int      create_philo(t_philo_gen *philo_gen);
int     join_philo(t_philo_gen *philo_gen);
void    free_resources(t_philo_gen *philo_gen);
void    check_die(t_philo_gen *philo_gen, t_philo *philosophers);
int	    algo_loop(t_philo **head);
void	eating_loop(t_philo **head);
int	    simulation_loop(t_main **head);
int	    is_death(t_main **head);
int	    do_work(t_main *arg);
void	*routine(void *head);
unsigned long long	gettime_milisec(void);
int	    ft_msleep(int time);
unsigned long	ft_atoi(char *str);
#endif
