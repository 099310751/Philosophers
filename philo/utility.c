#include "philosopher.h"
#include "utility.h"
#include <unistd.h>
#include <time.h>



pthread_mutex_t g_stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

int check_eat_count(t_philo_gen *philo_gen)
{
int i;
i = 0;
while (i < philo_gen->num_of_philo)
{
    if (philo_gen->philosophers[i].eat_count < philo_gen->num_of_must_eat)
        return (0);
    i++;
}
return (1);
}

void print_status(int philosopher_id, int status)
{
pthread_mutex_lock(&g_stdout_mutex);
ft_putnbr(get_time_ms());
ft_putstr(" ");
ft_putnbr(philosopher_id);
ft_putstr(" ");
if (status == 1)
ft_putstr("is thinking\n");
else if (status == 2)
ft_putstr("has taken a fork\n");
else if (status == 3)
ft_putstr("is eating\n");
else if (status == 4)
ft_putstr("is sleeping\n");
else if (status == 5)
ft_putstr("died\n");
pthread_mutex_unlock(&g_stdout_mutex);
}

void think()
{
usleep(1000000);
}

void eat()
{
usleep(1000000);
}

void ft_sleep()
{
usleep(1000000);
}

void take_forks(int left_fork, int right_fork)
{
(void)left_fork;
(void)right_fork;
printf("Philosopher takes forks\n");
}

void put_forks(int left_fork, int right_fork)
{
(void)left_fork;
(void)right_fork;
printf("Philosopher puts down forks\n");
}

int is_time_to_die()
{
return 0;
}

void    ft_putnbr(int n)
{
    if (n < 0)
    {
        putchar('-');
        n = -n;
    }
    if (n > 9)
        ft_putnbr(n / 10);
    putchar(n % 10 + '0');
}

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        putchar(str[i]);
        i++;
    }
}