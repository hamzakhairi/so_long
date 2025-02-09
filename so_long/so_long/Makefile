CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
MLX = -Lminilibx-linux -lmlx -lXext -lX11
SRC = so_long.c read_file.c valide_map.c free_map.c get_next_line.c get_next_line_utils.c init_window.c handle_keypress.c render_map.c
OBJ = $(SRC:.c=.o)
NAME = so_long

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
