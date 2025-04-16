/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:34 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/16 18:48:17 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	parse_file(t_game *game, char *file_path)
{
	if (!validate_file(file_path))
		return (false);
	if (!load_file_content(game, file_path))
		return (false);
	if (!parse_textures(game))
		return (false);
	if (!parse_map(game))
		return (false);
	return (true);
}

bool	validate_file(char *file_path)
{	
	if (!file_path)
		return (false);
	if (!is_valid_ext(file_path, ".cub"))
	{
		ft_printf("Error\nInvalid file extension. Expected .cub\n");
		return (false);
	}
	
	int fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\nCould not open file: %s\n", file_path);
		return (false);
	}
	close(fd);
	
	return (true);
}

bool	load_file_content(t_game *game, char *file_path)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	fd = open(file_path, O_RDONLY);
	if (fd < 0)
		return (false);
	
	content = ft_strdup("");
	if (!content)
		return (false);
	
	while ((line = get_next_line(fd)) != NULL)
	{
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		free(line);
		if (!content)
		{
			close(fd);
			return (false);
		}
	}
	
	close(fd);
	game->file = ft_split(content, '\n');
	free(content);
	
	if (!game->file)
		return (false);
	
	return (true);
}