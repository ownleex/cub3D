/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/20 18:57:44 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	find_map_start(t_game *game)
{
	int	i;
	int	j;

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
game->file[i][j] != ' ')
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
	int	i;
	int	j;
	int	height;

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
game->file[i][j] != ' ')
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
	int	i;
	int	max_width;
	int	line_width;

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
	int	i;
	int	j;

	game->map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!game->map)
		return (false);
	i = 0;
	while (i < height)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (width + 1));
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
		game->map[i][width] = '\0';
		i++;
	}
	game->map[height] = NULL;
	return (true);
}

bool	set_player_position(t_game *game, int x, int y, char dir)
{
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	if (dir == 'N')
	{
		game->player.dir.x = 0;
		game->player.dir.y = -1;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0;
		game->player.dir.y = 1;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = 0.66;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1;
		game->player.dir.y = 0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
	}
	game->map[y][x] = '0';
	return (true);
}

bool	find_player(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (false);
				set_player_position(game, x, y, game->map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

bool	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width && game->map[y][x] == ' ')
			x++;
		if (x < game->map_width && game->map[y][x] != '1')
			return (false);
		x = game->map_width - 1;
		while (x >= 0 && game->map[y][x] == ' ')
			x--;
		if (x >= 0 && game->map[y][x] != '1')
			return (false);
		y++;
	}
	x = 0;
	while (x < game->map_width)
	{
		y = 0;
		while (y < game->map_height && game->map[y][x] == ' ')
			y++;
		if (y < game->map_height && game->map[y][x] != '1')
			return (false);
		y = game->map_height - 1;
		while (y >= 0 && game->map[y][x] == ' ')
			y--;
		if (y >= 0 && game->map[y][x] != '1')
			return (false);
		x++;
	}
	return (true);
}

bool	check_map_closed(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
			{
				if (y == 0 || y == game->map_height - 1 || x == 0 || x == game->map_width - 1)
					return (false);
				if (game->map[y - 1][x] == ' ' || game->map[y + 1][x] == ' ' || game->map[y][x - 1] == ' ' || game->map[y][x + 1] == ' ')
					return (false);
			}
			x++;
		}
		y++;
	}
	return (true);
}

bool	check_map_chars(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' && \
game->map[y][x] != 'N' && game->map[y][x] != 'S' && \
game->map[y][x] != 'E' && game->map[y][x] != 'W' && \
game->map[y][x] != ' ')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

bool	validate_map(t_game *game)
{
	if (!check_map_chars(game))
	{
		printf("Error\nInvalid characters in map\n");
		return (false);
	}
	if (!find_player(game))
	{
		printf("Error\nMap must contain exactly one player position (N, S, E, or W)\n");
		return (false);
	}
	if (!check_map_borders(game))
	{
		printf("Error\nMap borders must be walls (1) or surrounded by walls\n");
		return (false);
	}
	if (!check_map_closed(game))
	{
		printf("Error\nMap must be completely enclosed by walls\n");
		return (false);
	}
	return (true);
}

bool	parse_map(t_game *game)
{
	int	start;
	int	height;
	int	width;

	start = find_map_start(game);
	if (start < 0)
	{
		printf("Error\nCould not find map in file\n");
		return (false);
	}
	height = count_map_height(game, start);
	if (height <= 0)
	{
		printf("Error\nInvalid map height\n");
		return (false);
	}
	width = get_map_width(game, start, height);
	if (width <= 0)
	{
		printf("Error\nInvalid map width\n");
		return (false);
	}
	if (!extract_map(game, start, height, width))
	{
		printf("Error\nFailed to extract map\n");
		return (false);
	}
	game->map_height = height;
	game->map_width = width;
	return (validate_map(game));
}
