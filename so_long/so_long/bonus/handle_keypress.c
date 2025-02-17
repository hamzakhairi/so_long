/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:40:44 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/17 18:01:07 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handel_open_exit(t_game *game)
{
	int	img_width;
	int	img_height;

	if (game->img_exit)
	{
		mlx_destroy_image(game->mlx, game->img_exit);
		game->img_exit = mlx_xpm_file_to_image(game->mlx,
				"./texter/exit_open.xpm", &img_width, &img_height);
	}
}

void	handle_exit_key(t_game *game, int keycode)
{
	if (keycode == 65307)
	{
		free_game(game);
		exit(0);
	}
}

void	handle_door(t_game *game, int new_x, int new_y, int *character)
{
	static int	olde_x;
	static int	olde_y;

	if (game->map[new_y][new_x] == 'E')
	{
		olde_x = new_x;
		olde_y = new_y;
		*character = 1;
	}
	else
	{
		*character = 0;
	}
	game->old_x = olde_x;
	game->old_y = olde_y;
}

void	process_movement(t_game *game, int keycode)
{
	int			dx;
	int			dy;
	int			new_x;
	int			new_y;
	static int	character;

	get_movement(keycode, &dx, &dy);
	handel_image_player(game, dx, dy);
	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	handle_door(game, new_x, new_y, &character);
	if (is_valid_move(game, new_x, new_y) && (dx != -2) && (dx != -2))
		update_position(game, new_x, new_y, character);
}

int	handle_keypress(int keycode, t_game *game)
{
	handle_exit_key(game, keycode);
	process_movement(game, keycode);
	return (0);
}
