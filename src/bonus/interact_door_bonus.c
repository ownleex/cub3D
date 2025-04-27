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

void    interact_door(t_game *game)
{
    int check_x;
    int check_y;
    t_door *door;

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