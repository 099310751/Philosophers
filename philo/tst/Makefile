CC=gcc
CFLAGS=-Werror -Wall -Wextra

SRCS=main.c 
OBJS=$(SRCS:.c=.o)

NAME=philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
