/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interact_door_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/27 16:23:58 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	interact_door(t_game *game)
{
	int		check_x;
	int		check_y;
	t_door	*door;

	check_x = (int)(game->player.pos.x + game->player.dir.x);
	check_y = (int)(game->player.pos.y + game->player.dir.y);
	door = game->door_list;
	while (door)
	{
		if (door->x == check_x && door->y == check_y)
		{
			door->is_open = !door->is_open;
			break ;
		}
		door = door->next;
	}
}
