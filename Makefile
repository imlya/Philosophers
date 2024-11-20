NAME= philo
FILES= eat.c init.c main.c parse.c print.c routine.c setter_getter.c time.c
OBJS= $(FILES:.c=.o)
CC= cc
FLAGS= -Wall -Wextra -Werror -g3 -pthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re