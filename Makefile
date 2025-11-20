NAME = fractol
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = main.c pixels.c initiale.c events.c atod.c
OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
	$(CC) $(OBJ)  -L/usr/include/minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lz -o $(NAME) -lm

%.o : %.c
	$(CC) $(CFLAGS) -c $< -I/usr/include/minilibx-linux  -o $@

all: $(NAME)
clean:
	rm -rf $(OBJ)
fclean: clean
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re
