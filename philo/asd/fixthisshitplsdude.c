Refactor this project to make it look unqiue,by making it work from one folder,also merge header files into one in philo.h,also change other file names and as much as u can varibale names
providing file names and codes:
philo.h
#ifndef PHILO_H
#define PHILO_H
#include "philos.structs.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/time.h>

void				ft_putstr(char *str);
void				print_header(void);
void				print_header_2(void);
void				print_header_3(void);
int					check_ac(int ac);
int					check_wrong_arguments(char **av);
int					checker_is_nall(t_main arg, int ac);
int					checker(int ac, char **av);
int					error_and_exit(void);
int					do_work(t_main *arg);
unsigned long long	gettime_milisec(void);
int					ft_msleep(int mili_sec);
int					set_mtx(t_main	*arg);
unsigned long		ft_atoi(char *str);
void				*routine(void *head);
int					algo_loop(t_philo **head);
void				eating_loop(t_philo **head);
int					simulation_loop(t_main **head);
int					is_death(t_main **head);
int					args_to_struct(t_main *arg, char **av);

#endif

philo.structs.h
#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#include <pthread.h>

typedef struct s_philo
{
	int					finished_flag;
	int					died;
	unsigned int		id;
	unsigned long		count_eating_time;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	unsigned long		count_time_to_eat;
	unsigned long long	contenue_time;
	unsigned long long	last_eat_time;
	pthread_t			philo;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
}				t_philo;

typedef struct s_main
{
	unsigned int	i;
	unsigned int	count_finished_philos;
	unsigned int	philo_id;
	unsigned int	fork_index;
	unsigned int	number_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	count_time_to_eat;
	t_philo			*philo_x;
	pthread_mutex_t	*mtx;
}				t_main;

#endif

check_input_arguments.c
#include "philo.h"

int	check_ac(int ac)
{
	if (ac == 5 || ac == 6)
		return (1);
	return (0);
}

int	check_wrong_arguments(char **av)
{
	int	i;
	int	j;

	i = 0;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (0);
	}
	return (1);
}

int	checker(int ac, char **av)
{
	if (!check_ac(ac))
	{
		write(2, "Error: something is wrong!\n", 27);
		return (-1);
	}
	if (!check_wrong_arguments(av))
	{
		write(2, "Error: something is wrong!\n", 27);
		return (-1);
	}
	return (0);
}

int	checker_is_nall(t_main arg, int ac)
{
	if (arg.number_of_philo <= 0 \
		|| arg.time_to_die <= 0 \
		|| arg.time_to_eat <= 0 \
		|| arg.time_to_sleep <= 0)
		return (-1);
	if (ac == 6 && arg.count_time_to_eat <= 0)
	{
		write(2, "Error: something is wrong!\n", 27);
		return (-1);
	}
	return (0);
}

init.c
#include "philo.h"
#include <pthread.h>

int	args_to_struct(t_main *arg, char **av)
{
	arg->number_of_philo = (unsigned)ft_atoi(av[1]);
	arg->time_to_die = ft_atoi(av[2]);
	arg->time_to_eat = ft_atoi(av[3]);
	arg->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		arg->count_time_to_eat = ft_atoi(av[5]);
	else
		arg->count_time_to_eat = 0;
	return (0);
}

int	set_mtx(t_main	*arg)
{
	arg->philo_id = 0;
	arg->fork_index = 0;
	while (arg->philo_id + 1 < arg->number_of_philo)
	{
		arg->philo_x[arg->philo_id].id = arg->philo_id + 1;
		arg->philo_x[arg->philo_id].left = &arg->mtx[arg->fork_index];
		arg->philo_x[arg->philo_id].right = &arg->mtx[arg->fork_index + 1];
		arg->philo_x[arg->philo_id].time_to_die = arg->time_to_die;
		arg->philo_x[arg->philo_id].time_to_eat = arg->time_to_eat;
		arg->philo_x[arg->philo_id].time_to_sleep = arg->time_to_sleep;
		arg->philo_x[arg->philo_id].count_time_to_eat = arg->count_time_to_eat;
		arg->philo_id++;
		arg->fork_index++;
	}
	arg->philo_x[arg->philo_id].id = arg->philo_id + 1;
	arg->philo_x[arg->philo_id].left = &arg->mtx[arg->fork_index];
	arg->philo_x[arg->philo_id].right = &arg->mtx[0];
	arg->philo_x[arg->philo_id].time_to_die = arg->time_to_die;
	arg->philo_x[arg->philo_id].time_to_eat = arg->time_to_eat;
	arg->philo_x[arg->philo_id].time_to_sleep = arg->time_to_sleep;
	arg->philo_x[arg->philo_id].count_time_to_eat = arg->count_time_to_eat;
	return (0);
}

void	*routine(void *head)
{
	t_philo				*data;

	data = head;
	data->count_eating_time = 0;
	data->contenue_time = gettime_milisec();
	data->last_eat_time = gettime_milisec();
	data->finished_flag = 0;
	if (data->id % 2 == 0)
		usleep(50);
	algo_loop(&data);
	return (0);
}

int	do_work(t_main *arg)
{
	unsigned int	i;

	i = 0;
	while (i < arg->number_of_philo)
	{
		pthread_mutex_init(&arg->mtx[i], NULL);
		i++;
	}
	i = 0;
	while (i < arg->number_of_philo)
	{
		pthread_create(&(arg->philo_x[i].philo), \
				NULL, &routine, &(arg->philo_x[i]));
		pthread_detach(arg->philo_x[i].philo);
		i++;
	}
	usleep(100);
	simulation_loop(&arg);
	i = 0;
	while (i < arg->number_of_philo)
	{
		pthread_mutex_destroy(&arg->mtx[i]);
		i++;
	}
	return (0);
}

loop.c
#include "philo.h"

int	is_death(t_main **head)
{
	if (gettime_milisec() - (*head)->philo_x[(*head)->i].last_eat_time \
		>= (*head)->time_to_die \
		&& (*head)->philo_x[(*head)->i].finished_flag == 0)
	{
		printf("%llu %u is died\n", \
				gettime_milisec(), \
				(*head)->philo_x[(*head)->i].id);
		return (-1);
	}
	return (0);
}

int	simulation_loop(t_main **head)
{
	(*head)->count_finished_philos = 0;
	while (1)
	{
		(*head)->i = 0;
		while ((*head)->i < (*head)->number_of_philo)
		{
			if ((*head)->count_finished_philos == (*head)->number_of_philo)
				return (1);
			if (is_death(&(*head)) == -1)
				return (-1);
			if ((*head)->philo_x[(*head)->i].finished_flag == 1)
			{
				(*head)->philo_x[(*head)->i].finished_flag++;
				(*head)->count_finished_philos++;
			}
			(*head)->i++;
		}
	}
	return (0);
}

int	algo_loop(t_philo **head)
{
	t_philo	*data;

	data = *head;
	while (1)
	{
		eating_loop(&data);
		data->contenue_time = gettime_milisec();
		data->count_eating_time++;
		if (data->count_eating_time == data->count_time_to_eat)
		{
			printf("%llu %u philo has finished simulation\n", \
			data->contenue_time, data->id);
			data->finished_flag++;
			return (0);
		}
		printf("%llu %u fall a sleep\n", data->contenue_time, data->id);
		ft_msleep(data->time_to_sleep);
		data->contenue_time = gettime_milisec();
		printf("%llu %u is thinking\n", data->contenue_time, data->id);
	}
	return (0);
}

void	eating_loop(t_philo **head)
{
	t_philo	*data;

	data = *head;
	pthread_mutex_lock(data->left);
	printf("%llu %u has taken a left fork\n", \
	data->contenue_time, data->id);
	pthread_mutex_lock(data->right);
	printf("%llu %u has taken a right fork\n", \
	data->contenue_time, data->id);
	data->last_eat_time = gettime_milisec();
	printf("%llu %u is eating\n", data->contenue_time, data->id);
	ft_msleep(data->time_to_eat);
	pthread_mutex_unlock(data->left);
	pthread_mutex_unlock(data->right);
}

main.c
#include "philo.h"

int	main(int ac, char **av)
{	
	t_main			arg;
	t_philo			*data;

	if (checker(ac, av))
		return (-1);
	args_to_struct(&arg, av);
	if (checker_is_nall(arg, ac) != 0)
		return (-1);
	data = malloc(sizeof(t_philo) * arg.number_of_philo);
	arg.mtx = malloc(sizeof(pthread_mutex_t) * arg.number_of_philo);
	if (ac == 6)
		data->count_time_to_eat = arg.count_time_to_eat;
	else
		data->count_time_to_eat = 0;
	arg.philo_x = data;
	set_mtx(&arg);
	do_work(&arg);
	free(data);
	free(arg.mtx);
	return (0);
}

philo_utils.c
#include "philo.h"

void	ft_putstr(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, &str[i], 1);
}

unsigned long	ft_atoi(char *str)
{
	unsigned long	res;
	int				i;

	res = 0;
	i = -1;
	while (str[++i])
	{
		res *= 10;
		res += str[i] - '0';
	}
	return (res);
}

unsigned long long	gettime_milisec(void)
{
	struct timeval		curent_time;
	unsigned long long	tv_msec;

	gettimeofday(&curent_time, NULL);
	tv_msec = curent_time.tv_sec * 1000 + curent_time.tv_usec / 1000;
	return (tv_msec);
}

int	ft_msleep(int time)
{
	unsigned long long	fixed_tv_msec;
	unsigned long long	curent_tv_msec;
	unsigned long long	mili_sec;

	mili_sec = time;
	fixed_tv_msec = gettime_milisec();
	curent_tv_msec = gettime_milisec();
	while (curent_tv_msec - fixed_tv_msec < mili_sec)
	{
		usleep(10);
		curent_tv_msec = gettime_milisec();
	}
	return (0);
}

Makefile
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./inc 

OBJS_DIR = obj
SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, $(OBJS_DIR)/%.o, $(SRCS))

MK = mkdir -p
RM = rm -f
RMRF = rm -rf

$(OBJS_DIR)/%.o: ./src/%.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -pthread

$(OBJS_DIR):
	@$(MK) $(OBJS_DIR)

clean:
	@$(RMRF)	$(OBJS_DIR)

fclean: clean
	@$(RM)  $(NAME)
	@$(RMRF) $(LIBCACH)

re: fclean all

.PHONY: all clean fclean re