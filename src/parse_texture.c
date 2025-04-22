/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/20 20:50:48 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_color_value(char *str, int *rgb)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		if (ft_isdigit(str[i]))
		{
			if (count >= 3)
				return (false);
			rgb[count] = ft_atoi(&str[i]);
			if (rgb[count] < 0 || rgb[count] > 255)
				return (false);
			count++;
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		if (str[i] == ',')
			i++;
		else if (str[i] && str[i] != ' ' && str[i] != '\t')
			return (false);
	}
	return (count == 3);
}

bool	parse_color(t_game *game, char *line, char type)
{
	int		rgb[3];
	int		color;
	char	*value;

	value = line + 1;
	while (*value && (*value == ' ' || *value == '\t'))
		value++;
	if (!parse_color_value(value, rgb))
	{
		printf("Error\nInvalid color format: %s\n", line);
		return (false);
	}
	color = create_rgb(rgb[0], rgb[1], rgb[2]);
	if (type == 'F')
		game->tex.floor = color;
	else
		game->tex.ceiling = color;
	return (true);
}

bool	parse_texture_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (load_texture(game, &game->tex.north, line + 3));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (load_texture(game, &game->tex.south, line + 3));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (load_texture(game, &game->tex.west, line + 3));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (load_texture(game, &game->tex.east, line + 3));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(game, line, 'F'));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(game, line, 'C'));
	return (true);
}

bool	check_textures_loaded(t_game *game)
{
	if (!game->tex.north.img || !game->tex.south.img || !game->tex.east.img || !game->tex.west.img)
		return (false);
	return (true);
}

bool	parse_textures(t_game *game)
{
	int	i;

	i = 0;
	while (game->file[i])
	{
		if (game->file[i][0] == '\0')
		{
			i++;
			continue ;
		}
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 || \
ft_strncmp(game->file[i], "SO ", 3) == 0 || \
ft_strncmp(game->file[i], "WE ", 3) == 0 || \
ft_strncmp(game->file[i], "EA ", 3) == 0 || \
ft_strncmp(game->file[i], "F ", 2) == 0 || \
ft_strncmp(game->file[i], "C ", 2) == 0)
		{
			if (!parse_texture_line(game, game->file[i]))
				return (false);
		}
		i++;
	}
	return (check_textures_loaded(game));
}
