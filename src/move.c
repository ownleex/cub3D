/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:34:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/17 17:18:18 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_exterior_wall(t_game *game, int x, int y)
{
	if (x == 0 || y == 0 || x == game->map_width - 1 || y == game->map_height - 1)
		return (true);
	if (x > 0 && game->map[y][x - 1] == ' ')
		return (true);
	if (x < game->map_width - 1 && game->map[y][x + 1] == ' ')
		return (true);
	if (y > 0 && game->map[y - 1][x] == ' ')
		return (true);
	if (y < game->map_height - 1 && game->map[y + 1][x] == ' ')
		return (true);
	return (false);
}

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
			return;
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
			return;
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
			return;
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
			return;
	}
	game->player.pos.x = new_x;
	game->player.pos.y = new_y;
}

void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir.x;
	game->player.dir.x = game->player.dir.x * cos(angle) - game->player.dir.y * sin(angle);
	game->player.dir.y = old_dir_x * sin(angle) + game->player.dir.y * cos(angle);
	old_plane_x = game->player.plane.x;
	game->player.plane.x = game->player.plane.x * cos(angle) - game->player.plane.y * sin(angle);
	game->player.plane.y = old_plane_x * sin(angle) + game->player.plane.y * cos(angle);
}