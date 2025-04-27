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

int	is_blocked(t_game *game, int x, int y)
{
	t_door	*door;

	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		door = game->door_list;
		while (door)
		{
			if (door->x == x && door->y == y)
			{
				if (door->is_open == 0)
					return (1);
			}
			door = door->next;
		}
	}
	return (0);
}
