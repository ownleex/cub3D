/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:35:02 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/28 19:29:55 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_file(t_game *game)
{
	int	i;

	if (!game->file)
		return ;
	i = 0;
	while (game->file[i])
	{
		free(game->file[i]);
		i++;
	}
	free(game->file);
	game->file = NULL;
}

void	free_door(t_game *game)
{
	t_door	*door;
	t_door	*next;

	door = game->door_list;
	while (door)
	{
		next = door->next;
		free(door);
		door = next;
	}
	game->door_list = NULL;
}
