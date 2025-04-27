/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cparodi <cparodi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/27 13:05:53 by cparodi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

bool	get_map_params(t_game *game, int *start, int *height, int *width)
{
	*start = find_map_start(game);
	if (*start < 0)
	{
		printf("Error\nCould not find map in file\n");
		return (false);
	}
	*height = count_map_height(game, *start);
	if (*height <= 0)
	{
		printf("Error\nInvalid map height\n");
		return (false);
	}
	*width = get_map_width(game, *start, *height);
	if (*width <= 0)
	{
		printf("Error\nInvalid map width\n");
		return (false);
	}
	return (true);
}

bool	parse_map(t_game *game)
{
	int		start;
	int		height;
	int		width;

	if (!get_map_params(game, &start, &height, &width))
		return (false);
	if (!extract_map(game, start, height, width))
	{
		printf("Error\nFailed to extract map\n");
		return (false);
	}
	game->map_height = height;
	game->map_width = width;
	return (validate_map(game));
}

static t_door *create_door(int x, int y)
{
    t_door *door = malloc(sizeof(t_door));
    if (!door)
        return (NULL);
    door->x = x;
    door->y = y;
    door->is_open = 0;
    door->next = NULL;
    return (door);
}

void find_door(t_game *game)
{
    int x;
	int y;
    t_door *new_door;

    y = 0;
    while (y < game->map_height)
    {
        x = 0;
        while (x < game->map_width)
        {
            if (game->map[y][x] == 'D')
            {
                new_door = create_door(x, y);
                new_door->next = game->door_list;
                game->door_list = new_door;
            }
            x++;
        }
        y++;
    }
}
