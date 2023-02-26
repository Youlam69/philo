NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror -pthread
# -fsanitize=thread
INCLUDE = philo.h

SRC = philo.c\
	atoi.c\
	parsing.c\
	thread_file.c\
	utils.c

OBJ = $(SRC:.c=.o)

#  //// should i use object file to compil //*/**/

all: $(NAME)

$(NAME): $(SRC) $(INCLUDE)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

fclean:
	rm -rf $(NAME)

re: fclean all