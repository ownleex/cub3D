/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:04 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/13 23:32:13 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	find_map_start(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	// Skip texture and color configurations
	while (game->file[i])
	{
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 ||
			ft_strncmp(game->file[i], "SO ", 3) == 0 ||
			ft_strncmp(game->file[i], "WE ", 3) == 0 ||
			ft_strncmp(game->file[i], "EA ", 3) == 0 ||
			ft_strncmp(game->file[i], "F ", 2) == 0 ||
			ft_strncmp(game->file[i], "C ", 2) == 0 ||
			game->file[i][0] == '\0')
		{
			i++;
			continue;
		}
		// Check if this line contains map characters
		j = 0;
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' &&
				game->file[i][j] != 'N' && game->file[i][j] != 'S' &&
				game->file[i][j] != 'E' && game->file[i][j] != 'W' &&
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
		// Check if this is still part of the map
		while (game->file[i][j])
		{
			if (game->file[i][j] != '0' && game->file[i][j] != '1' &&
				game->file[i][j] != 'N' && game->file[i][j] != 'S' &&
				game->file[i][j] != 'E' && game->file[i][j] != 'W' &&
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
	for (i = start; i < start + height; i++)
	{
		line_width = ft_strlen(game->file[i]);
		if (line_width > max_width)
			max_width = line_width;
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
	
	for (i = 0; i < height; i++)
	{
		game->map[i] = (char *)malloc(sizeof(char) * (width + 1));
		if (!game->map[i])
			return (false);
		
		// Copy the line and pad with spaces
		for (j = 0; j < width; j++)
		{
			if (j < (int)ft_strlen(game->file[start + i]))
				game->map[i][j] = game->file[start + i][j];
			else
				game->map[i][j] = ' ';
		}
		game->map[i][width] = '\0';
	}
	game->map[height] = NULL;
	return (true);
}

bool	set_player_position(t_game *game, int x, int y, char dir)
{
	// Set player position
	game->player.pos.x = x + 0.5;
	game->player.pos.y = y + 0.5;
	
	// Set player direction and plane based on the map character
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
	// Replace player character with floor in the map
	game->map[y][x] = '0';
	return (true);
}

bool	find_player(t_game *game)
{
	int	x;
	int	y;
	int	player_count;

	player_count = 0;
	for (y = 0; y < game->map_height; y++)
	{
		for (x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == 'N' || game->map[y][x] == 'S' ||
				game->map[y][x] == 'E' || game->map[y][x] == 'W')
			{
				if (player_count > 0)
					return (false); // More than one player position
				set_player_position(game, x, y, game->map[y][x]);
				player_count++;
			}
		}
	}
	return (player_count == 1);
}

bool	check_map_borders(t_game *game)
{
	int	x;
	int	y;

	// Check horizontal borders
	for (y = 0; y < game->map_height; y++)
	{
		// Find first non-space character from left
		x = 0;
		while (x < game->map_width && game->map[y][x] == ' ')
			x++;
		if (x < game->map_width && game->map[y][x] != '1')
			return (false);
		
		// Find first non-space character from right
		x = game->map_width - 1;
		while (x >= 0 && game->map[y][x] == ' ')
			x--;
		if (x >= 0 && game->map[y][x] != '1')
			return (false);
	}
	
	// Check vertical borders
	for (x = 0; x < game->map_width; x++)
	{
		// Find first non-space character from top
		y = 0;
		while (y < game->map_height && game->map[y][x] == ' ')
			y++;
		if (y < game->map_height && game->map[y][x] != '1')
			return (false);
		
		// Find first non-space character from bottom
		y = game->map_height - 1;
		while (y >= 0 && game->map[y][x] == ' ')
			y--;
		if (y >= 0 && game->map[y][x] != '1')
			return (false);
	}
	
	return (true);
}

bool	check_map_closed(t_game *game)
{
	int	x;
	int	y;

	for (y = 0; y < game->map_height; y++)
	{
		for (x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] == '0')
			{
				// Check if surrounded by walls or valid spaces
				if (y == 0 || y == game->map_height - 1 || 
					x == 0 || x == game->map_width - 1)
					return (false);
				
				// Check adjacent cells
				if (game->map[y-1][x] == ' ' || game->map[y+1][x] == ' ' ||
					game->map[y][x-1] == ' ' || game->map[y][x+1] == ' ')
					return (false);
			}
		}
	}
	return (true);
}

bool	check_map_chars(t_game *game)
{
	int	x;
	int	y;

	for (y = 0; y < game->map_height; y++)
	{
		for (x = 0; x < game->map_width; x++)
		{
			if (game->map[y][x] != '0' && game->map[y][x] != '1' &&
				game->map[y][x] != 'N' && game->map[y][x] != 'S' &&
				game->map[y][x] != 'E' && game->map[y][x] != 'W' &&
				game->map[y][x] != ' ')
				return (false);
		}
	}
	return (true);
}

bool	validate_map(t_game *game)
{
	if (!check_map_chars(game))
	{
		ft_printf("Error\nInvalid characters in map\n");
		return (false);
	}
	if (!find_player(game))
	{
		ft_printf("Error\nInvalid player position (must be exactly one N, S, E, or W)\n");
		return (false);
	}
	if (!check_map_borders(game))
	{
		ft_printf("Error\nMap borders must be walls (1) or surrounded by walls\n");
		return (false);
	}
	if (!check_map_closed(game))
	{
		ft_printf("Error\nMap must be completely enclosed by walls\n");
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
		ft_printf("Error\nCould not find map in file\n");
		return (false);
	}
	
	height = count_map_height(game, start);
	if (height <= 0)
	{
		ft_printf("Error\nInvalid map height\n");
		return (false);
	}
	
	width = get_map_width(game, start, height);
	if (width <= 0)
	{
		ft_printf("Error\nInvalid map width\n");
		return (false);
	}
	
	if (!extract_map(game, start, height, width))
	{
		ft_printf("Error\nFailed to extract map\n");
		return (false);
	}
	
	game->map_height = height;
	game->map_width = width;
	
	return (validate_map(game));
}