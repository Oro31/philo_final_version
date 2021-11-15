CFLAGS = -Wall -Wextra -Werror

NAME = philosopher

SRC = ft_atoi.c	\
	  ft_init.c	\
	  ft_is_int.c	\
	  ft_mutex.c	\
	  ft_satiated.c	\
	  ft_status.c	\
	  ft_thread.c	\
	  ft_time.c	\
	  main.c

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	clang $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

flemme: re
	make clean

.PHONY: clean fclean all re
