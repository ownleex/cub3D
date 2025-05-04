/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:18:00 by cparodi           #+#    #+#             */
/*   Updated: 2025/05/03 23:06:46 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.y * MOVE_SPEED;
	if (!is_exterior_wall(game, (int)new_x, (int)game->player.pos.y))
		game->player.pos.x = new_x;
	if (!is_exterior_wall(game, (int)game->player.pos.x, (int)new_y))
		game->player.pos.y = new_y;
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.x * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.y * MOVE_SPEED;
	if (!is_exterior_wall(game, (int)new_x, (int)game->player.pos.y))
		game->player.pos.x = new_x;
	if (!is_exterior_wall(game, (int)game->player.pos.x, (int)new_y))
		game->player.pos.y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x + game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y - game->player.dir.x * MOVE_SPEED;
	if (!is_exterior_wall(game, (int)new_x, (int)game->player.pos.y))
		game->player.pos.x = new_x;
	if (!is_exterior_wall(game, (int)game->player.pos.x, (int)new_y))
		game->player.pos.y = new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos.x - game->player.dir.y * MOVE_SPEED;
	new_y = game->player.pos.y + game->player.dir.x * MOVE_SPEED;
	if (!is_exterior_wall(game, (int)new_x, (int)game->player.pos.y))
		game->player.pos.x = new_x;
	if (!is_exterior_wall(game, (int)game->player.pos.x, (int)new_y))
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
