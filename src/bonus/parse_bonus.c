/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 23:31:34 by ayarmaya          #+#    #+#             */
/*   Updated: 2025/04/23 00:16:35 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	open_file(char *file_path)
{
	int	fd;

	if (!file_path)
		return (-1);
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\nCould not open file: %s\n", file_path);
		return (-1);
	}
	return (fd);
}

bool	load_file_content(t_game *game, int fd)
{
	char	*line;
	char	*content;
	char	*temp;

	content = ft_strdup("");
	if (!content)
		return (false);
	line = get_next_line(fd);
	while (line)
	{
		temp = content;
		content = ft_strjoin(content, line);
		free(temp);
		free(line);
		if (!content)
			return (false);
		line = get_next_line(fd);
	}
	game->file = ft_split(content, '\n');
	free(content);
	if (!game->file)
		return (false);
	return (true);
}

bool	parse_file(t_game *game, char *file_path)
{
	int	fd;

	fd = open_file(file_path);
	if (fd < 0)
		return (false);
	if (!load_file_content(game, fd))
	{
		close(fd);
		return (false);
	}
	close(fd);
	if (!parse_textures(game))
		return (false);
	if (!parse_map(game))
		return (false);
	return (true);
}

t_game	parsing(t_game game, char *argv)
{
	if (!init_mlx(&game))
	{
		printf("Error\nFailed to initialize MLX\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	if (!parse_file(&game, argv))
		clean_exit(&game, EXIT_FAILURE);
	if (!init_player(&game))
	{
		printf("Error\nFailed to initialize player\n");
		clean_exit(&game, EXIT_FAILURE);
	}
	return (game);
}
