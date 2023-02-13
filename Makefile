NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread

INCLUDE = philo.h

SRC = philo.c\
	atoi.c\
	parsing.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all