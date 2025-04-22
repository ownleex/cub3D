/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/22 19:23:17 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
