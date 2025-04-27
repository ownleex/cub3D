/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/25 03:17:34 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_blocked(t_game *game, int x, int y)
{
	if (game->map[y][x] == '1')
		return (1);
	if (game->map[y][x] == 'D')
	{
		t_door *door = game->door_list;
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
