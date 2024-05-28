Name = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = philo_bonus.c utils_bonus.c init_bonus.c routin_bonus.c free_bonus.c ft_putnbr_fd.c

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