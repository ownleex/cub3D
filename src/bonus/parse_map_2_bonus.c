/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 18:45:47 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/22 21:29:27 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	find_map_start(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (game->file[i])
	{
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 || \
ft_strncmp(game->file[i], "SO ", 3) == 0 || \
ft_strncmp(game->file[i], "WE ", 3) == 0 || \
ft_strncmp(game->file[i], "EA ", 3) == 0 || \
ft_strncmp(game->file[i], "F ", 2) == 0 || \
ft_strncmp(game->file[i], "C ", 2) == 0 || \
game->file[i][0] == '\0')
		{
			i++;
			continue ;
		}
		j = 0;
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' && \
game->file[i][j] != 'N' && game->file[i][j] != 'S' && \
game->file[i][j] != 'E' && game->file[i][j] != 'W' && \
game->file[i][j] != ' ' && game->file[i][j] != 'D')
				break ;
			j++;
		}
		if (game->file[i][j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

int	count_map_height(t_game *game, int start)
{
	int		i;
	int		j;
	int		height;

	i = start;
	height = 0;
	while (game->file[i])
	{
		j = 0;
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' && \
game->file[i][j] != 'N' && game->file[i][j] != 'S' && \
game->file[i][j] != 'E' && game->file[i][j] != 'W' && \
game->file[i][j] != ' ' && game->file[i][j] != 'D')
				return (height);
			j++;
		}
		height++;
		i++;
	}
	return (height);
}

int	get_map_width(t_game *game, int start, int height)
{
	int		i;
	int		max_width;
	int		line_width;

	max_width = 0;
	i = start;
	while (i < start + height)
	{
		line_width = ft_strlen(game->file[i]);
		if (line_width > max_width)
			max_width = line_width;
		i++;
	}
	return (max_width);
}

bool	extract_map(t_game *game, int start, int height, int width)
{
	int		i;
	int		j;

	game->map = malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (false);
	i = 0;
	while (i < height)
	{
		game->map[i] = malloc(sizeof(char) * (width + 1));
		if (!game->map[i])
			return (false);
		j = 0;
		while (j < width)
		{
			if (j < (int)ft_strlen(game->file[start + i]))
				game->map[i][j] = game->file[start + i][j];
			else
				game->map[i][j] = ' ';
			j++;
		}
		game->map[i++][width] = '\0';
	}
	game->map[height] = NULL;
	return (true);
}
