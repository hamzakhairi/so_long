/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:40:44 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/09 20:47:28 by hkhairi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_exit(t_game	*game)
{
	printf("You win!\n");
	mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE / 2 - 50,
		game->map_height * TILE_SIZE / 2, 0x00FF00, "You win!");
	mlx_do_sync(game->mlx);
	sleep(2);
	free_game(game);
	exit(0);
}

void	update_position(t_game *game, int new_x, int new_y , int yes, int od_x, int od_y)
{
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
		handle_exit(game);
	game->map[game->player_y][game->player_x] = '0';
	if (!yes && od_x != 0 && od_y != 0)
	{
		game->map[od_y][od_x] = 'E';
	}
	game->map[new_y][new_x] = 'P';
	game->player_x = new_x;
	game->player_y = new_y;
	game->moves++;
	render_map(game);
}

int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_x < 0 || new_x >= game->map_width
		|| new_y < 0 || new_y >= game->map_height)
		return (0);
	if (game->map[new_y][new_x] == '1')
		return (0);
	return (1);
}

void	get_movement(int keycode, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (keycode == 65361)
		*dx = -1;
	else if (keycode == 65363)
		*dx = 1;
	else if (keycode == 65362)
		*dy = -1;
	else if (keycode == 65364)
		*dy = 1;
}

int	handle_keypress(int keycode, t_game *game)
{
	int	dx;
	int	dy;
	int	new_x;
	int	new_y;
	static int character;
	static int olde_x;
	static int olde_y;

	if (keycode == 65307)
	{
		free_game(game);
		exit(0);
	}
	get_movement(keycode, &dx, &dy);
	new_x = game->player_x + dx;
	new_y = game->player_y + dy;
	if (game->map[new_y][new_x] == 'E')
	{
		olde_x = new_x;
		olde_y = new_y;
		character = 1;
	}
	else
		character = 0;
	if (is_valid_move(game, new_x, new_y))
		update_position(game, new_x, new_y, character, olde_x, olde_y);
	return (0);
}
