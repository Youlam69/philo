NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread
INCLUDE = philo.h

SRC = philo.c\
	parsing.c\
	thread_file.c\
	utils.c

# atoi.c\

OBJ = $(SRC:.c=.o)

#  //// should i use object file to compil //*/**/

all: $(NAME)

$(NAME): $(OBJ) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)
clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(NAME) $(OBJ)

re: fclean all