/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 16:03:34 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/08 10:33:29 by hkhairi          ###   ########.fr       */
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

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img_wall;
	void	*img_player;
	void	*img_collect;
	void	*img_exit;
	void	*img_empty;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
	int		collectibles;
	int		moves;
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
	int	exit_reachable;
	int	collectibles_reachable;
	int	rows;
}	t_valid;

// Function prototypes
char	**read_map(char *file);
t_map	size_map(char **map);
int		valid_wall(char **map);
t_valid	valide(char **map);
void	free_map(char **map);
t_point	find_player(char **map);
char	**copy_map(char **map, int rows);
void	flood_fill(char **map, int x, int y, t_valid *game);
int		validate_map(char **map, t_valid *game);
void	init_game(t_game *game, char *file_name);
void	render_map(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	free_images(t_game *game);
void	free_game(t_game *game);

#endif
