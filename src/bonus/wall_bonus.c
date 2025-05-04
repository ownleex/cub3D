/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 18:30:40 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/05/04 01:12:45 by ayarmaya         ###   ########.fr       */
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
