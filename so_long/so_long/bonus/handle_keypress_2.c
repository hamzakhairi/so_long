/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keypress_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhairi <hkhairi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:10:22 by hkhairi           #+#    #+#             */
/*   Updated: 2025/02/15 16:24:33 by hkhairi          ###   ########.fr       */
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

void	handle_failed(t_game *game)
{
	printf("Game Over!\n");
	mlx_string_put(game->mlx, game->win, game->map_width * TILE_SIZE / 2 - 50,
		game->map_height * TILE_SIZE / 2, 0x00FF00, "Game Over!");
	mlx_do_sync(game->mlx);
	sleep(2);
	free_game(game);
	exit(0);
}

void	update_position(t_game *game, int new_x, int new_y, int yes)
{
	if (game->map[new_y][new_x] == 'C')
		game->collectibles--;
	if (game->map[new_y][new_x] == 'M')
		handle_failed(game);
	if (game->map[new_y][new_x] == 'E' && game->collectibles == 0)
		handle_exit(game);
	game->map[game->player_y][game->player_x] = '0';
	if (!yes && game->old_y != 0 && game->old_x != 0)
	{
		game->map[game->old_y][game->old_x] = 'E';
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
