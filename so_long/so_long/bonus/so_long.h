/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:03:34 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/16 15:37:37 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "./minilibx-linux/mlx.h"
# include "./get_next_line.h"
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>

# define TILE_SIZE 32

typedef struct s_enemy
{

	int		enemy_x;
	int		enemy_y;
	int		direction_image;
	int		direction;
}	t_enemy;

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_player;
	void	*img_collect;
	void	*img_exit;
	void	*img_empty;
	void	*img_enemy;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
	int		old_x;
	int		old_y;
	int		num_enemies;
	t_enemy	*arr_enemy;
}	t_game;

typedef struct s_map_game {
	int	x;
	int	y;
}	t_map_game;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	int	i;
	int	j;
}	t_map;

typedef struct s_valid
{
	int	space;
	int	wall;
	int	exit;
	int	player;
	int	collectibl;
	int	enemy;
}	t_valid;

// Function prototypes
char	**read_map(char *file);
t_map	size_map(t_game *game);
int		valid_wall(char **map);
void	valide(t_game *game);
void	free_map(char **map);
t_point	find_player(char **map);
char	**copy_map(char **map, int rows);
void	flood_fill(char **map, int x, int y);
void	init_game(t_game *game, char *file_name);
void	render_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	free_images(t_game *game);
void	free_game(t_game *game);
void	validate_map(t_game *game);
char	*ft_strdup_str(char	*src);
void	get_movement(int keycode, int *dx, int *dy);
int		is_valid_move(t_game *game, int new_x, int new_y);
void	update_position(t_game *game, int new_x, int new_y, int yes);
int		check_copy_map(char **map, int row);
void	cheack_player(int x, int y, t_game *game);
void validate_component_map(t_game *game);
void	handle_failed(t_game *game);
int game_loop(t_game *game);
void handel_image_player(t_game *game, int dx, int dy);
void	free_enemy(t_game *game);
void	free_all_component(t_game	*game);
void	find_enemy_positions(t_game *game);

#endif