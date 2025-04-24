/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/24 17:12:46 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	init_mlx(t_game *game)
{
	int	i;

	i = 0;
	while (i < 128)
	{
		game->keys[i] = 0;
		i++;
	}
	game->key_left = 0;
	game->key_right = 0;
	game->mouse_captured = 0;
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

bool	init_player(t_game *game)
{
	if (game->player.dir.x == 0 && game->player.dir.y == 0)
		return (false);
	if (game->player.plane.x == 0 && game->player.plane.y == 0)
		return (false);
	return (true);
}
