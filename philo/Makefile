NAME= philo
CC= cc
FLAGS= -Wall -Wextra -Werror -g3 -pthread #-fsanitize=thread 
FILES= eat.c init.c main.c parse.c routine.c routine_utils.c setter_getter.c supervise.c time.c
OBJS= $(FILES:.c=.o)

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
