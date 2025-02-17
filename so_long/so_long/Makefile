# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/16 21:13:11 by hkhairi           #+#    #+#              #
#    Updated: 2025/02/17 18:06:05 by hkhairi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I.
MLX_DIR = ./minilibx-linux
MLX = -L$(MLX_DIR) -lmlx -lXext -lX11

MANDATORY_PART = ./mandatory
SRC = $(MANDATORY_PART)/so_long.c $(MANDATORY_PART)/FloodFill_2.c $(MANDATORY_PART)/read_file.c $(MANDATORY_PART)/valide_map_2.c $(MANDATORY_PART)/handle_keypress_2.c $(MANDATORY_PART)/valide_map.c $(MANDATORY_PART)/FloodFill.c $(MANDATORY_PART)/free_map.c $(MANDATORY_PART)/get_next_line.c $(MANDATORY_PART)/get_next_line_utils.c $(MANDATORY_PART)/init_window.c $(MANDATORY_PART)/handle_keypress.c $(MANDATORY_PART)/render_map.c
OBJ = $(SRC:.c=.o)
NAME = so_long
HEADER_FILE_MANDATORY = $(MANDATORY_PART)/so_long.h

NAME_BONUS = so_long_bonus
BONUS_PART = ./bonus
SRC_BONUS = $(BONUS_PART)/put_string.c $(BONUS_PART)/draw_move_player.c $(BONUS_PART)/FloodFill_2.c $(BONUS_PART)/free_map.c $(BONUS_PART)/handel_image.c $(BONUS_PART)/handle_keypress.c $(BONUS_PART)/init_window.c $(BONUS_PART)/move_enemy_2.c $(BONUS_PART)/read_file.c $(BONUS_PART)/so_long.c $(BONUS_PART)/valide_map_2.c $(BONUS_PART)/FloodFill.c $(BONUS_PART)/get_next_line.c $(BONUS_PART)/get_next_line_utils.c $(BONUS_PART)/handle_keypress_2.c $(BONUS_PART)/move_enemy.c $(BONUS_PART)/render_map.c $(BONUS_PART)/valide_map.c
OBJ_BONUS = $(SRC_BONUS:.c=.o)
HEADER_FILE_BONUS = $(BONUS_PART)/so_long.h

all: $(NAME)

bonus: $(NAME_BONUS)


$(NAME_BONUS): $(OBJ_BONUS) $(HEADER_FILE_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX) -o $(NAME_BONUS)

$(NAME): $(OBJ) $(HEADER_FILE_MANDATORY)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

re: fclean all



# CC = gcc
# CFLAGS = -Wall -Wextra -Werror -I.
# MLX_DIR = minilibx-linux
# MLX = -L$(MLX_DIR) -lmlx -lXext -lX11

# MANDATORY_PART = ./mandatory
# SRC = $(MANDATORY_PART)/so_long.c $(MANDATORY_PART)/FloodFill_2.c $(MANDATORY_PART)/read_file.c $(MANDATORY_PART)/valide_map_2.c $(MANDATORY_PART)/handle_keypress_2.c $(MANDATORY_PART)/valide_map.c $(MANDATORY_PART)/FloodFill.c $(MANDATORY_PART)/free_map.c $(MANDATORY_PART)/get_next_line.c $(MANDATORY_PART)/get_next_line_utils.c $(MANDATORY_PART)/init_window.c $(MANDATORY_PART)/handle_keypress.c $(MANDATORY_PART)/render_map.c
# OBJ = $(SRC:.c=.o)
# NAME = so_long
# HEADER_FILE_MANDATORY = ./mandatory/so_long.h

# NAME_BONUS = so_long_bonus
# BONUS_PART = ./bonus
# SRC_BONUS = $(BONUS_PART)/so_long.c $(BONUS_PART)/FloodFill_2.c $(BONUS_PART)/read_file.c $(BONUS_PART)/valide_map_2.c $(BONUS_PART)/handle_keypress_2.c $(BONUS_PART)/valide_map.c $(BONUS_PART)/FloodFill.c $(BONUS_PART)/free_map.c $(BONUS_PART)/get_next_line.c $(BONUS_PART)/get_next_line_utils.c $(BONUS_PART)/init_window.c $(BONUS_PART)/handle_keypress.c $(BONUS_PART)/render_map.c
# OBJ_BONUS = $(SRC_BONUS:.c=.o)
# HEADER_FILE_BONUS = ./bonus/so_long.h

# all: $(NAME)

# bouns: $(NAME_BONUS)

# $(NAME_BONUS): $(OBJ_BONUS) 
# 	$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX) -o $(NAME_BONUS)

# $(NAME): $(OBJ) 
# 	$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

# %.o: %.c $(HEADER_FILE_MANDATORY) $(HEADER_FILE_BONUS)
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all
