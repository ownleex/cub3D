/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:45:39 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/22 19:23:07 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_map_chars(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' && \
game->map[y][x] != 'N' && game->map[y][x] != 'S' && \
game->map[y][x] != 'E' && game->map[y][x] != 'W' && \
game->map[y][x] != ' ')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_row_borders(t_game *game)
{
	int		y;
	int		x;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width && game->map[y][x] == ' ')
			x++;
		if (x < game->map_width && game->map[y][x] != '1')
			return (false);
		x = game->map_width - 1;
		while (x >= 0 && game->map[y][x] == ' ')
			x--;
		if (x >= 0 && game->map[y][x] != '1')
			return (false);
		y++;
	}
	return (true);
}

bool	check_col_borders(t_game *game)
{
	int		x;
	int		y;

	x = 0;
	while (x < game->map_width)
	{
		y = 0;
		while (y < game->map_height && game->map[y][x] == ' ')
			y++;
		if (y < game->map_height && game->map[y][x] != '1')
			return (false);
		y = game->map_height - 1;
		while (y >= 0 && game->map[y][x] == ' ')
			y--;
		if (y >= 0 && game->map[y][x] != '1')
			return (false);
		x++;
	}
	return (true);
}

bool	check_map_closed(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
			{
				if (y == 0 || y == game->map_height - 1 || \
x == 0 || x == game->map_width - 1)
					return (false);
				if (game->map[y - 1][x] == ' ' || \
game->map[y + 1][x] == ' ' || \
game->map[y][x - 1] == ' ' || \
game->map[y][x + 1] == ' ')
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map(t_game *game)
{
	if (!check_map_chars(game))
	{
		printf("Error\nInvalid characters in map\n");
		return (false);
	}
	if (!find_player(game))
	{
		printf("Error\nMap must contain exactly one player \
position (N, S, E, or W)\n");
		return (false);
	}
	if (!check_map_borders(game))
	{
		printf("Error\nMap borders must be walls (1) or surrounded by walls\n");
		return (false);
	}
	if (!check_map_closed(game))
	{
		printf("Error\nMap must be completely enclosed by walls\n");
		return (false);
	}
	return (true);
}
