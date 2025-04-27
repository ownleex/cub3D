/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:18:20 by cparodi           #+#    #+#             */
/*   Updated: 2025/04/27 16:18:22 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_exterior_wall(t_game *game, int x, int y)
{
	if (x == 0 || y == 0 || x == game->map_width - 1 || \
y == game->map_height - 1)
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
