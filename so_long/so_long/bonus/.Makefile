# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .Makefile                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 15:26:37 by hkhairi           #+#    #+#              #
#    Updated: 2025/02/16 21:41:52 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# SRC_BONUS = $(BONUS_PART)/so_long.c $(BONUS_PART)/FloodFill_2.c $(BONUS_PART)/read_file.c $(BONUS_PART)/valide_map_2.c $(BONUS_PART)/handle_keypress_2.c $(BONUS_PART)/valide_map.c $(BONUS_PART)/FloodFill.c $(BONUS_PART)/free_map.c $(BONUS_PART)/get_next_line.c $(BONUS_PART)/get_next_line_utils.c $(BONUS_PART)/init_window.c $(BONUS_PART)/handle_keypress.c $(BONUS_PART)/render_map.c


CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
#-fsanitize=address
MLX = -Lminilibx-linux -lmlx -lXext -lX11 
SRC = FloodFill_2.c  free_map.c  handel_image.c       handle_keypress.c  init_window.c    move_enemy_2.c  read_file.c   so_long.c  valide_map_2.c \
	FloodFill.c    get_next_line.c  get_next_line_utils.c  handle_keypress_2.c   move_enemy.c    render_map.c   valide_map.c
# so_long.c FloodFill_2.c move_enemy_2.c handel_image.c move_enemy.c read_file.c valide_map_2.c handle_keypress_2.c valide_map.c FloodFill.c free_map.c get_next_line.c get_next_line_utils.c init_window.c handle_keypress.c render_map.c
OBJ = $(SRC:.c=.o)
NAME = so_long
HEADER_FIL = so_long.h
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c $(HEADER_FIL)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
