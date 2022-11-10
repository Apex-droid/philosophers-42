NAME = philo

SRC = check_deth.c clean.c disp_thr.c disp_utils.c eat_count.c init.c mem.c parser.c phi_life.c philo.c prints.c time_ut.c

CC = gcc -pthread -O3 -Wall -Werror -Wextra

HEAD = philo.h

all:$(NAME)

$(NAME):$(SRC) $(HEAD)
	$(CC) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

norm:
	norminette $(SRC)
	norminette $(HEAD)

re: fclean all

PHONY: all clean fclean re