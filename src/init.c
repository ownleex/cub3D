/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:26:46 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	create_texture(t_game *game, t_texture *texture, int width, int height)
{
	texture->img = mlx_new_image(game->mlx, width, height);
	if (!texture->img)
		return (false);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	texture->width = width;
	texture->height = height;
	return (true);
}

bool	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (false);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (false);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (false);
	game->img_addr = mlx_get_data_addr(game->img, &game->img_bits_per_pixel,
			&game->img_line_length, &game->img_endian);
	return (true);
}

bool	init_texture_data(t_game *game)
{
	bool	success;

	success = true;
	if (!parse_textures(game))
		success = false;
	game->textures_loaded = success;
	return (success);
}

bool	init_player(t_game *game)
{
	// Player direction and plane are initialized during map parsing
	// based on the player's starting orientation (N, S, E, W)
	// This function is called to ensure the player has been initialized correctly
	if (game->player.dir.x == 0 && game->player.dir.y == 0)
		return (false);
	if (game->player.plane.x == 0 && game->player.plane.y == 0)
		return (false);
	return (true);
}

bool	init_game(t_game *game)
{
	if (!init_mlx(game))
		return (false);
	if (!init_texture_data(game))
		return (false);
	if (!init_player(game))
		return (false);
	return (true);
}