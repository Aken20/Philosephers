Name = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = philo.c utils.c init.c routin.c free.c ft_putnbr_fd.c forks.c

OBJ = $(SRC:%.c=%.o)

all: $(Name)

$(Name): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -lpthread -o $(Name)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(Name)

re: fclean all

.PHONY: all clean fclean re