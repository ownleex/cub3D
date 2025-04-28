/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_blocked_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/27 16:31:49 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_minimap_door(t_game *game, int i, int j, int size)
{
	t_door	*door;

	door = game->door_list;
	while (door)
	{
		if (door->x == j && door->y == i)
		{
			if (door->is_open)
				draw_minimap_square(game, (t_vector){j, i}, \
size, 0x00FF00);
			else
				draw_minimap_square(game, (t_vector){j, i}, \
size, 0xFF0000);
			break;
		}
		door = door->next;
	}
}
