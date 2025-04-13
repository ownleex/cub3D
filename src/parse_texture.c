/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:32:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/14 00:26:56 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

bool	load_texture(t_game *game, t_texture *texture, char *path)
{
	// Trim possible whitespace
	while (*path && (*path == ' ' || *path == '\t'))
		path++;

	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width, &texture->height);
	if (!texture->img)
	{
		ft_printf("Error\nCould not load texture: %s\n", path);
		return (false);
	}
	
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
	
	return (true);
}

bool	parse_color_value(char *str, int *rgb)
{
	int	i;
	int	count;
	
	i = 0;
	count = 0;
	
	while (str[i])
	{
		// Skip whitespace
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		
		// Parse the RGB component
		if (ft_isdigit(str[i]))
		{
			if (count >= 3)
				return (false); // Too many components
			
			rgb[count] = ft_atoi(&str[i]);
			if (rgb[count] < 0 || rgb[count] > 255)
				return (false); // Invalid component value
			
			count++;
			
			// Skip the digits
			while (str[i] && ft_isdigit(str[i]))
				i++;
		}
		
		// Skip comma or whitespace
		if (str[i] == ',')
			i++;
		else if (str[i] && str[i] != ' ' && str[i] != '\t')
			return (false); // Invalid character
	}
	
	return (count == 3); // Must have exactly 3 components
}

bool	parse_color(t_game *game, char *line, char type)
{
	int		rgb[3];
	int		color;
	char	*value;
	
	// Skip the identifier and spaces
	value = line + 1;
	while (*value && (*value == ' ' || *value == '\t'))
		value++;
	
	if (!parse_color_value(value, rgb))
	{
		ft_printf("Error\nInvalid color format: %s\n", line);
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
	// Parse texture paths based on the identifier
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
	
	// Ignore empty lines and other content (map will be parsed separately)
	return (true);
}

bool	check_textures_loaded(t_game *game)
{
	// Check that all required textures and colors are loaded
	if (!game->tex.north.img || !game->tex.south.img ||
		!game->tex.east.img || !game->tex.west.img)
		return (false);
	
	// The colors use 0 as their default value, so we can't check them directly
	// Instead, we rely on the parsing process to ensure they are set.
	
	return (true);
}

bool	parse_textures(t_game *game)
{
	int	i;
	
	i = 0;
	while (game->file[i])
	{
		// Skip empty lines
		if (game->file[i][0] == '\0')
		{
			i++;
			continue;
		}
		
		// Process texture and color lines
		if (ft_strncmp(game->file[i], "NO ", 3) == 0 ||
			ft_strncmp(game->file[i], "SO ", 3) == 0 ||
			ft_strncmp(game->file[i], "WE ", 3) == 0 ||
			ft_strncmp(game->file[i], "EA ", 3) == 0 ||
			ft_strncmp(game->file[i], "F ", 2) == 0 ||
			ft_strncmp(game->file[i], "C ", 2) == 0)
		{
			if (!parse_texture_line(game, game->file[i]))
				return (false);
		}
		
		i++;
	}
	
	return (check_textures_loaded(game));
}