/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:30:40 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/23 00:16:00 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
