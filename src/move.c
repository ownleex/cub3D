/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:18:00 by cparodi           #+#    #+#             */
/*   Updated: 2025/04/27 16:18:02 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map[map_y][map_x] == '1')
	{
		if (is_exterior_wall(game, map_x, map_y))
			return ;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map[map_y][map_x] == '1')
	{
		if (is_exterior_wall(game, map_x, map_y))
			return ;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map[map_y][map_x] == '1')
	{
		if (is_exterior_wall(game, map_x, map_y))
			return ;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (game->map[map_y][map_x] == '1')
	{
		if (is_exterior_wall(game, map_x, map_y))
			return ;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(angle) - \
game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + \
game->player.dir.y * cos(angle);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(angle) - \
game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + \
game->player.plane.y * cos(angle);
}
