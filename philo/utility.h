#ifndef UTILITY_H
# define UTILITY_H
#include <pthread.h>
#include <stdio.h>
#include "philosopher.h"

int check_eat_count(t_philo_gen *philo_gen);
void print_status(int id, int status);
void    think();
void    eat();
void    take_forks(int left_fork, int right_fork);
void    put_forks(int left_fork, int right_fork);
void    ft_sleep();
int    is_time_to_die(void);
int is_dead(t_philo *philo);
void    ft_putstr(char *str);
void    ft_putnbr(int n);
unsigned long get_time_ms();
#endif
