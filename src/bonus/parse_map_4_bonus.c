/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_4_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:45:35 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/22 21:29:42 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	set_ns_direction(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir.x = 0.0;
		player->dir.y = -1.0;
		player->plane.x = 0.66;
		player->plane.y = 0.0;
	}
	else if (dir == 'S')
	{
		player->dir.x = 0.0;
		player->dir.y = 1.0;
		player->plane.x = -0.66;
		player->plane.y = 0.0;
	}
}

void	set_ew_direction(t_player *player, char dir)
{
	if (dir == 'E')
	{
		player->dir.x = 1.0;
		player->dir.y = 0.0;
		player->plane.x = 0.0;
		player->plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir.x = -1.0;
		player->dir.y = 0.0;
		player->plane.x = 0.0;
		player->plane.y = -0.66;
	}
}

bool	set_player_position(t_game *game, int x, int y, char dir)
{
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	if (dir == 'N' || dir == 'S')
		set_ns_direction(&game->player, dir);
	else if (dir == 'E' || dir == 'W')
		set_ew_direction(&game->player, dir);
	game->map[y][x] = '0';
	return (true);
}

bool	find_player(t_game *game)
{
	int		x;
	int		y;
	int		player_count;

	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' || \
game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (false);
				set_player_position(game, x, y, game->map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

bool	check_map_borders(t_game *game)
{
	if (!check_row_borders(game))
		return (false);
	if (!check_col_borders(game))
		return (false);
	return (true);
}
